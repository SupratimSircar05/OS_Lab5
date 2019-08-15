#include <stdio.h>
#include <stdlib.h>

#define totalprocess 5

typedef struct process {
    int at, bt, pr, pno;
} process;

process proc[totalprocess];

int comparator(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

void get_wt_time(int wt[]) {
    int service[50];

    service[0] = 0;
    wt[0] = 0;

    for (int i = 1; i < totalprocess; i++) {
        service[i] = proc[i - 1].bt + service[i - 1];

        wt[i] = service[i] - proc[i].at + 1;

        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }

}

void get_tat_time(int tat[], const int wt[]) {
    for (int i = 0; i < totalprocess; i++) {
        tat[i] = proc[i].bt + wt[i];
    }
}

void findgc() {

    int wt[50], tat[50];

    double wavg = 0, tavg = 0;


    get_wt_time(wt);

    get_tat_time(tat, wt);

    int stime[50], ctime[50];
    stime[0] = 1;
    ctime[0] = stime[0] + tat[0];


    for (int i = 1; i < totalprocess; i++) {
        stime[i] = ctime[i - 1];
        ctime[i] = stime[i] + tat[i] - wt[i];
    }

    printf("ProcessNo.\tPriorityNo.\tArrivalTime\tBurstTime\tCompletionTime\tTurnAroundTime\tWaitingTime\tResponseTime\n\n");


    for (int i = 0; i < totalprocess; i++) {
        wavg += wt[i];
        tavg += tat[i];

        printf("%d \t\t\t\t%d \t\t%d \t\t\t\t%d \t\t\t\t%d \t\t\t\t\t%d \t\t\t%d \t\t\t %d\n", proc[i].pno, proc[i].pr,
               proc[i].at,
               proc[i].bt, ctime[i], tat[i],
               wt[i], (stime[i] - proc[i].at));
    }

    printf("Average waiting time is : ");
    printf("%f\n", wavg / (float) totalprocess);
    printf("Average turnaround time : ");
    printf("%f\n", tavg / (float) totalprocess);

}

int main() {

    for (int i = 0; i < totalprocess; i++) {
        printf("\nEnter Process No., Arrival Time, Burst Time, Priority No. for (process %d) :\n", (i + 1));
        scanf("%d", &proc[i].pno);
        scanf("%d", &proc[i].at);
        scanf("%d", &proc[i].bt);
        scanf("%d", &proc[i].pr);
    }

    qsort(proc, totalprocess, sizeof(proc[0]), comparator);

    findgc();

    return 0;
}
