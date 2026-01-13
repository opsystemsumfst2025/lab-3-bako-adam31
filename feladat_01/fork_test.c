#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Indulás előtt: Egy folyamat vagyok (PID: %d)\n", getpid());

    pid_t pid = fork(); // Itt történik a hasadás

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Gyermek kód
        printf("Én vagyok a Gyerek! A PID-em: %d, a Szülőm PID-je: %d\n", 
               getpid(), getppid());
    } else {
        // Szülő kód
        printf("Én vagyok a Szülő! A PID-em: %d, a Gyerekem PID-je: %d\n", 
               getpid(), pid);
    }

    return 0;
}
