#include <stdio.h>

// Function to write input data to input.txt
void writeInputToFile() {
    FILE *inputFile = fopen("input.txt", "w");
    if (inputFile == NULL) {
        printf("Error opening input file!\n");
        return;
    }

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    fprintf(inputFile, "%d\n", n); // Write number of processes to the file

    // Write Arrival Time and Burst Time for each process
    for (int i = 0; i < n; i++) {
        int at, bt;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &at, &bt);
        fprintf(inputFile, "%d %d\n", at, bt); // Write Arrival Time and Burst Time to the file
    }

    fclose(inputFile);
}

// Function to read the input file and perform FCFS scheduling
void readInputFromFileAndProcess() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file!\n");
        return;
    }

    int n;
    fscanf(inputFile, "%d", &n); // Read number of processes
    printf("\nNumber of processes: %d\n", n);

    int at[n], bt[n], ct[n], tat[n], wt[n]; // Arrays to store Arrival Time, Burst Time, Completion Time, Turnaround Time, Waiting Time

    // Read Arrival Time and Burst Time for each process
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d", &at[i], &bt[i]);
    }

    fclose(inputFile);

    // FCFS Scheduling Logic
    int t = 0; // Current time
    for (int i = 0; i < n; i++) {
        // If the process has arrived (at[i] <= t), we can start processing
        if (at[i] > t) {
            t = at[i]; // If current time is less than arrival time, move time forward
        }

        // Set Completion Time as current time + Burst Time
        ct[i] = t + bt[i];
        // Calculate Turnaround Time (Completion Time - Arrival Time)
        tat[i] = ct[i] - at[i];
        // Calculate Waiting Time (Turnaround Time - Burst Time)
        wt[i] = tat[i] - bt[i];

        // Move time forward by the Burst Time of the current process
        t = ct[i];
    }

    // Print the results for each process
    printf("\nP#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

int main() {
    // Step 1: Write input data to the file
    writeInputToFile();

    // Step 2: Read input data from the file and perform FCFS scheduling
    readInputFromFileAndProcess();

    return 0;
}