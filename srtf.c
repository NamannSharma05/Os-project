#include <stdio.h>
#include <limits.h>

int main(void) {
    int n;

    // Open input and output files
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Read the number of processes
    fscanf(inputFile, "%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], rt[n], remaining_bt[n];
    int completed = 0, current_time = 0, shortest_process_index, min_bt;

    // Read Arrival Time and Burst Time for each process
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d", &at[i], &bt[i]);
        remaining_bt[i] = bt[i]; // Initialize remaining burst time
        rt[i] = -1;              // Initialize response time
    }

    // SRTF Scheduling Algorithm
    while (completed < n) {
        shortest_process_index = -1;
        min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining_bt[i] > 0 && remaining_bt[i] < min_bt) {
                shortest_process_index = i;
                min_bt = remaining_bt[i];
            }
        }

        if (shortest_process_index == -1) { // No process is ready
            current_time++;
            continue;
        }

        if (rt[shortest_process_index] == -1) { // Update response time for the first execution
            rt[shortest_process_index] = current_time - at[shortest_process_index];
        }

        remaining_bt[shortest_process_index]--; // Execute the process for 1 unit of time
        current_time++;

        if (remaining_bt[shortest_process_index] == 0) { // Process completed
            completed++;
            ct[shortest_process_index] = current_time;
        }
    }

    // Calculate Turnaround Time and Waiting Time
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i]; // Turnaround Time
        wt[i] = tat[i] - bt[i]; // Waiting Time
    }

    // Write the results to the output file
    fprintf(outputFile, "P#\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    printf("SRTF scheduling results have been written to 'output.txt'.\n");

    return 0;
}
