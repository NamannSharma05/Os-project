#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int choice;

    printf("CPU Scheduling Algorithms:\n");
    printf("1. First Come First Serve (FCFS)\n");
    printf("2. Shortest Job First (SJF)\n");
    printf("3. Shortest Remaining Time First (SRTF)\n");
    printf("4. Priority Scheduling\n");
    printf("5. Round Robin (RR)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: system("gcc fcfs.c -o fcfs && ./fcfs"); break;
        case 2: system("gcc sjf.c -o sjf && ./sjf"); break;
        case 3: system("gcc srtf.c -o srtf && ./srtf"); break;
        case 4: system("gcc priority.c -o priority && ./priority"); break;
        case 5: system("gcc round_robin.c -o round_robin && ./round_robin"); break;
        default: printf("Invalid choice!\n"); break;
    }

    return 0;
}