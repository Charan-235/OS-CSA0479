#include <stdio.h>

// Structure to represent a process
typedef struct {
    int pid;         // Process ID
    int arrivalTime; // Arrival time of the process
    int burstTime;   // Burst time of the process
    int priority;    // Priority of the process
    int waitingTime; // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
} Process;

// Function to swap two processes
void swap(Process *p1, Process *p2) {
    Process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Function to sort processes based on arrival time and priority
void sortProcesses(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                swap(&processes[i], &processes[j]);
            } else if (processes[i].arrivalTime == processes[j].arrivalTime) {
                if (processes[i].priority < processes[j].priority) {
                    swap(&processes[i], &processes[j]);
                }
            }
        }
    }
}

// Function to calculate waiting time and turnaround time for each process
void calculateTimes(Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Calculate waiting time
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        if (processes[i].waitingTime < 0) {
            processes[i].waitingTime = 0;
        }

        // Calculate turnaround time
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;

        // Update current time
        currentTime += processes[i].burstTime;

        // Update total waiting time and turnaround time
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    // Print average waiting time and turnaround time
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

// Function to print process details
void printProcessDetails(Process processes[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);
    }
}

int main() {
    int n; // Number of processes

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Create an array of processes
    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter process ID, arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d %d", &processes[i].pid, &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
    }

    // Sort processes based on arrival time and priority
    sortProcesses(processes, n);

    // Calculate waiting time and turnaround time for each process
    calculateTimes(processes, n);

    // Print process details
    printProcessDetails(processes, n);

    return 0;
}
