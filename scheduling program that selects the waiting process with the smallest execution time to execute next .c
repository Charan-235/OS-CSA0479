#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;            // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int completionTime; // Completion Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
    int remainingTime;  // Remaining Time (for non-preemptive scheduling)
} Process;

int compareArrivalTime(const void* a, const void* b) {
    return ((Process*)a)->arrivalTime - ((Process*)b)->arrivalTime;
}

int compareBurstTime(const void* a, const void* b) {
    return ((Process*)a)->burstTime - ((Process*)b)->burstTime;
}

void calculateTimes(Process* processes, int n) {
    int completed = 0, currentTime = 0;
    int isCompleted[n]; // Array to track completed processes

    // Initialize the isCompleted array
    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0;
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (completed < n) {
        int idx = -1;
        int shortestBurst = 9999999;

        // Find the process with the smallest burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i] && processes[i].remainingTime < shortestBurst) {
                idx = i;
                shortestBurst = processes[i].remainingTime;
            }
        }

        if (idx != -1) {
            // Execute the selected process
            processes[idx].remainingTime = 0; // Mark the process as completed
            isCompleted[idx] = 1;
            completed++;
            currentTime += processes[idx].burstTime; // Update current time

            // Calculate Completion Time, Turnaround Time, and Waiting Time
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
        } else {
            // If no process is ready to execute, move the time forward
            currentTime++;
        }
    }
}

void printProcessDetails(Process* processes, int n) {
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i].pid,
            processes[i].arrivalTime,
            processes[i].burstTime,
            processes[i].completionTime,
            processes[i].turnaroundTime,
            processes[i].waitingTime);
    }
}

int main() {
    int n;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input details of each process
    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for Process %d: ", i + 1);
        processes[i].pid = i + 1;
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    // Sort processes based on arrival time
    qsort(processes, n, sizeof(Process), compareArrivalTime);

    // Calculate completion time, turnaround time, and waiting time
    calculateTimes(processes, n);

    // Print the process details
    printProcessDetails(processes, n);

    return 0;
}
