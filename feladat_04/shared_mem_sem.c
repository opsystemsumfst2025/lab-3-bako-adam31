#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

// Struktúra a közös adatokhoz
typedef struct {
    int counter;
    sem_t mutex;  // A szemafor is közös kell legyen!
} SharedData;

int main() {
    // Közös memória terület foglalása
    SharedData *data = mmap(NULL, sizeof(SharedData), 
                            PROT_READ | PROT_WRITE, 
                            MAP_SHARED | MAP_ANONYMOUS, 
                            -1, 0);
    
    if (data == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }
    
    data->counter = 0;
    
    // Semafor inicializálása:
    // - 1. paraméter: a szemafor címe
    // - 2. paraméter: 1 = process-shared (nem thread-shared!)
    // - 3. paraméter: 1 = kezdőérték (szabad állapot, mint egy nyitott zár)
    if (sem_init(&data->mutex, 1, 1) != 0) {
        perror("sem_init failed");
        return 1;
    }

    printf("Kezdőérték: %d\n", data->counter);
    printf("Mindkét folyamat 100 000-szer növeli (SZINKRONIZÁLTAN)...\n\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // GYEREK folyamat
        for (int i = 0; i < 100000; i++) {
            sem_wait(&data->mutex);  // LOCK - belépés a kritikus szakaszba
            data->counter++;
            sem_post(&data->mutex);  // UNLOCK - kilépés
        }
        printf("[Gyerek] Készen vagyok!\n");
        exit(0);
    } else {
        // SZÜLŐ folyamat
        for (int i = 0; i < 100000; i++) {
            sem_wait(&data->mutex);  // LOCK
            data->counter++;
            sem_post(&data->mutex);  // UNLOCK
        }
        printf("[Szülő] Készen vagyok!\n");
        
        wait(NULL); // Megvárjuk a gyereket
        
        printf("\n=================================\n");
        printf("Várt érték:    200 000\n");
        printf("Kapott érték:  %d\n", data->counter);
        printf("=================================\n");
        
        if (data->counter == 200000) {
            printf("\n✓ HELYES! A szemafor megvédte a kritikus szakaszt!\n");
        } else {
            printf("\n✗ Valami hiba van... (de ez nagyon ritka!)\n");
        }
        
        // Takarítás
        sem_destroy(&data->mutex);
        munmap(data, sizeof(SharedData));
    }

    return 0;
}
