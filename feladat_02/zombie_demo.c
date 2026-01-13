#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("[Szülő] Indulás... PID: %d\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // GYEREK folyamat
        printf("[Gyerek] Elindultam, PID: %d\n", getpid());
        printf("[Gyerek] Dolgozom 2 másodpercig...\n");
        sleep(2);
        printf("[Gyerek] Kész vagyok, kilépek.\n");
        exit(0);
    } else {
        // SZÜLŐ folyamat
        printf("[Szülő] A gyerekem PID-je: %d\n", pid);
        
        // ===== FIGYELEM! =====
        // Próbáld ki ELŐSZÖR úgy, hogy ez a rész kommentezve van!
        // Akkor zombie lesz a gyerek.
        // 
        // MÁSODSZOR uncomment-eld ki ezt:
        /*
        printf("[Szülő] Megvárom a gyereket...\n");
        wait(NULL);
        printf("[Szülő] A gyerek befejeződött, nincs több zombie!\n");
        */
        
        // =====================
        
        printf("[Szülő] Alszok 10 másodpercig...\n");
        printf("[Szülő] (Közben nyiss egy másik terminált és nézd meg: ps aux | grep defunct)\n");
        sleep(10);
        
        printf("[Szülő] Felébredtem, vége.\n");
    }

    return 0;
}
