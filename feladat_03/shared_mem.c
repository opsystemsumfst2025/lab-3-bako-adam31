#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    // Közös memória terület foglalása egy int számára
    // MAP_SHARED: megosztott a folyamatok között
    // MAP_ANONYMOUS: nincs mögötte fájl, csak memória
    int *counter = mmap(NULL, sizeof(int), 
                        PROT_READ | PROT_WRITE, 
                        MAP_SHARED | MAP_ANONYMOUS, 
                        -1, 0);
    
    if (counter == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }
    
    *counter = 0; // Kezdőérték

    printf("Kezdőérték: %d\n", *counter);
    printf("Mindkét folyamat 100 000-szer növeli...\n\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // GYEREK folyamat
        for (int i = 0; i < 100000; i++) {
            (*counter)++; // Versenyhelyzet!
        }
        printf("[Gyerek] Készen vagyok!\n");
        exit(0);
    } else {
        // SZÜLŐ folyamat
        for (int i = 0; i < 100000; i++) {
            (*counter)++; // Versenyhelyzet!
        }
        printf("[Szülő] Készen vagyok!\n");
        
        // Megvárjuk a gyereket
        wait(NULL);
        
        printf("\n=================================\n");
        printf("Várt érték:    200 000\n");
        printf("Kapott érték:  %d\n", *counter);
        printf("=================================\n");
        
        if (*counter != 200000) {
            printf("\n⚠️  RACE CONDITION!\n");
            printf("Az eredmény nem determinisztikus.\n");
            printf("Futtasd újra, más eredményt fogsz kapni!\n");
        }
        
        // Takarítás
        munmap(counter, sizeof(int));
    }

    return 0;
}
