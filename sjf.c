#include<stdio.h>

int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    int n;
    fscanf(inputFile, "%d", &n); // Read number of processes from file

    int at[n], bt[n], ct[n], tat[n], wt[n], rt[n], remaining_bt[n];
    int completed = 0, current_time = 0, shortest_process_index, min_bt = 1000;

    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d", &at[i], &bt[i]); // Read Arrival Time and Burst Time
        remaining_bt[i] = bt[i];
        rt[i] = -1; // Initialize response time to -1 (not yet started)
    }
    fclose(inputFile);

    while (completed < n) {
        shortest_process_index = -1;
        min_bt = 1000;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining_bt[i] > 0 && remaining_bt[i] < min_bt) {
                shortest_process_index = i;
                min_bt = remaining_bt[i];
            }
        }

        if (shortest_process_index == -1) { // Handle idle time if no process is ready
            current_time++;
            continue; // Skip the rest of the loop when no valid process is found
        }

        if (rt[shortest_process_index] == -1) { // Update response time for first execution
            rt[shortest_process_index] = current_time - at[shortest_process_index];
        }

        remaining_bt[shortest_process_index]--;
        current_time++;

        if (remaining_bt[shortest_process_index] == 0) {
            completed++;
            ct[shortest_process_index] = current_time;
        }
    }

    fprintf(outputFile, "P#\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        fprintf(outputFile, "P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    fclose(outputFile);
    printf("Scheduling results written to output.txt\n");
    return 0;
}
