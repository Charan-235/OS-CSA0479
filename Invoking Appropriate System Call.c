#include <stdio.h>
#include <unistd.h>  // For fork(), getpid(), getppid()
#include <sys/types.h>  // For pid_t

int main() {
    pid_t pid = fork();  // Create a new process

    if (pid < 0) {
        // Error occurred while forking
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child process:\n");
        printf("Process ID (PID): %d\n", getpid());
        printf("Parent Process ID (PPID): %d\n", getppid());
    } else {
        // Parent process
        printf("Parent process:\n");
        printf("Process ID (PID): %d\n", getpid());
        printf("Parent Process ID (PPID): %d\n", getppid());
    }

    return 0;
}
