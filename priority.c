#include <stdio.h>

int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    int n, i;
    fscanf(inputFile, "%d", &n); // Read number of processes
    
    int at[n], bt[n], priority[n], ct[n], tat[n], wt[n], rt[n], remaining_bt[n];
    int completed = 0, current_time = 0;

    for (i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d %d", &at[i], &bt[i], &priority[i]); // Read AT, BT, and Priority
        remaining_bt[i] = bt[i];
        rt[i] = -1; // Initialize Response Time
    }
    fclose(inputFile);

    while (completed < n) {
        int highest_priority_index = -1;
        int max_priority = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining_bt[i] > 0) {
                if (priority[i] > max_priority ||
                   (priority[i] == max_priority && remaining_bt[i] < remaining_bt[highest_priority_index])) {
                    max_priority = priority[i];
                    highest_priority_index = i;
                }
            }
        }

        if (highest_priority_index == -1) { // Handle idle time
            current_time++;
            continue;
        }

        if (rt[highest_priority_index] == -1) { // Update Response Time
            rt[highest_priority_index] = current_time - at[highest_priority_index];
        }

        remaining_bt[highest_priority_index]--;
        current_time++;

        if (remaining_bt[highest_priority_index] == 0) { // Process completes
            completed++;
            ct[highest_priority_index] = current_time;
        }
    }

    // Write results to output file
    fprintf(outputFile, "P#\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i]; // Turnaround Time
        wt[i] = tat[i] - bt[i]; // Waiting Time
        fprintf(outputFile, "P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], priority[i], ct[i], tat[i], wt[i], rt[i]);
    }
    fclose(outputFile);

    printf("Scheduling results written to output.txt\n");
    return 0;
}
