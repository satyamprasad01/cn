#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child: PID = %d\n", getpid());
        while (1){}
    } else {
        printf("Parent: PID = %d\n", getpid());
        while (1){}
    }
    return 0;
}
