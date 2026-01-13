// Házi feladat: Ping-Pong
// 
// Feladat: A szülő és a gyerek felváltva írja ki a PING és PONG szavakat.
// Használj két szemafort a szinkronizációhoz!
//
// Tipp: Az egyik szemafor kezdőértéke 1, a másiké 0.
//       Gondold át, melyik folyamat indul először!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

#define ROUNDS 10  // Hányszor ismétlődjön a ping-pong?

typedef struct {
    sem_t sem_parent;
    sem_t sem_child;
} SharedSems;

int main() {
    // Közös memória a szemaforoknak
    SharedSems *sems = mmap(NULL, sizeof(SharedSems),
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS,
                            -1, 0);
    
    if (sems == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }
    
    // TODO: Inicializáld a szemaforokat!
    // Melyik legyen 1 és melyik 0?
    // sem_init(&sems->sem_parent, 1, ???);
    // sem_init(&sems->sem_child, 1, ???);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid == 0) {
        // ========== GYEREK ==========
        
        for (int i = 0; i < ROUNDS; i++) {
            // TODO: Várd meg, hogy te jöhess
            // sem_wait(...);
            
            printf("PONG\n");
            
            // TODO: Engedd el a szülőt
            // sem_post(...);
        }
        
        exit(0);
    } else {
        // ========== SZÜLŐ ==========
        
        for (int i = 0; i < ROUNDS; i++) {
            // TODO: Várd meg, hogy te jöhess
            // sem_wait(...);
            
            printf("PING\n");
            
            // TODO: Engedd el a gyereket
            // sem_post(...);
        }
        
        wait(NULL);
        
        // Takarítás
        sem_destroy(&sems->sem_parent);
        sem_destroy(&sems->sem_child);
        munmap(sems, sizeof(SharedSems));
    }
    
    return 0;
}
