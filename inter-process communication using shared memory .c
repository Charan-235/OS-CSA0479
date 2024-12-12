#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

// Structure to represent shared memory
typedef struct {
    int data;
} SharedMemory;

int main() {
    // Create a shared memory segment
    int shm_id = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the current process
    SharedMemory* shm_ptr = (SharedMemory*)shmat(shm_id, NULL, 0);
    if (shm_ptr == (void*)-1) {
        perror("shmat");
        exit(1);
    }

    // Initialize the shared memory
    shm_ptr->data = 0;

    // Fork a new process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process: Shared memory data = %d\n", shm_ptr->data);
        shm_ptr->data = 10;
        printf("Child process: Shared memory data = %d\n", shm_ptr->data);
    } else {
        // Parent process
        sleep(1); // Wait for the child process to finish
        printf("Parent process: Shared memory data = %d\n", shm_ptr->data);
    }

    // Detach the shared memory segment from the current process
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Remove the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
