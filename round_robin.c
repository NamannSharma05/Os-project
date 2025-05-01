#include <stdio.h>

int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    int n, Q, i, t = 0, completed = 0;
    
    fscanf(inputFile, "%d", &n); // Read number of processes
    fscanf(inputFile, "%d", &Q); // Read time quantum

    int at[n], bt[n], ct[n], tat[n], wt[n], rem_bt[n];
    
    for (i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d", &at[i], &bt[i]); // Read Arrival Time and Burst Time
        rem_bt[i] = bt[i];
    }
    fclose(inputFile);

    while (completed < n) {
        int idle = 1;
        
        for (i = 0; i < n; i++) {
            if (rem_bt[i] > 0 && at[i] <= t) {
                idle = 0;
                
                if (rem_bt[i] > Q) {
                    t += Q;
                    rem_bt[i] -= Q;
                } else {
                    t += rem_bt[i];
                    rem_bt[i] = 0;
                    ct[i] = t;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    completed++;
                }
            }
        }
        
        if (idle) {
            t++;
        }
    }

    fprintf(outputFile, "P#\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        fprintf(outputFile, "P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    fclose(outputFile);

    printf("Scheduling results written to output.txt\n");
    return 0;
}
