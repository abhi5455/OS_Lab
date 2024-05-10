#include<stdio.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int priority;
    int remTime;
    int ct;
}Process;
Process Q1[20],Q2[20],Q3[20],Q4[20],JobQ[20];
int f=0, tf=0, r;
void display(Process P[20],int n)
{
    int i,comp=0,turn=0,wait=0;
    float totalTurn=0,totalWait=0;
    printf("+-----------------------------------------------------------------+\n");
    printf("|  PID  |  Priority  |   AT   |   BT   |   CT   |  TURN  |  WAIT  |\n");
    printf("|-----------------------------------------------------------------|\n");
    for(i=0;i<n;i++)
    {
        while(comp<P[i].at)
        {       comp++;
        }
        comp+=P[i].bt;
        turn=comp-P[i].at;
        wait=turn-P[i].bt;
        printf("|   P%d  | %6d     | %4d   | %4d   | %4d   | %4d   | %4d   |\n",P[i].pid,P[i].priority,P[i].at,P[i].bt,comp,turn,wait);
        totalTurn+=turn;
        totalWait+=wait;
    }
    printf("+-----------------------------------------------------------------+\n");
    printf("Average TurnAround Time = %.2f\n",totalTurn/n);
    printf("Average Waiting Time = %.2f\n",totalWait/n);
}
void JOBQ(Process P[20],int n)
{
    Process temp;
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(P[j].at > P[j+1].at){
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }
    for(i=0;i<n;i++) {
        JobQ[i] = P[i];
    }
}
void FPFS(int n)
{
    int i;
    for(i=0;i<n;i++) {
        Q1[i] = JobQ[i];
    }
    printf("\n\t\t\tFPFS\n");
    display(Q1,n);
}
void SJF(Process P[20],int n)
{
    int i,j,total;
    Process temp;
    for(i=0;i<n;i++){
        total=0;
        for(j=0;j<n-i-1;j++) {
            if ((P[j].bt > P[j + 1].bt )&& (P[j + 1].at <= total)) {
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
            total+=P[j].bt;
        }
    }
    printf("\n\n\t\t\tSJF\n");
    display(P,n);
    /*for(i=0;i<n;i++) {
        Q4[i] = P[i];
    }*/
}
void Priority(int n)
{
    int i,j;
    Process temp;
    for(i=0;i<n;i++) {
        Q2[i] = JobQ[i];
    }
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++) {
            if ((Q2[j].priority > Q2[j + 1].priority )&& (Q2[j + 1].at <= Q2[j].at)) {
                temp = Q2[j];
                Q2[j] = Q2[j + 1];
                Q2[j + 1] = temp;
            }
        }
    }
    printf("\n\n\t\t\tPriority\n");
    display(Q2,n);
}
Process dequeue(Process* P,int* front)
{
    Process temp=P[*front];
    (*front)++;
    return temp;
}
void SJFroundRobin(Process* P,int start,int n, int ts)
{
    int i,j,total;
    Process temp;
    if(n<=1)
    {
        P[0].remTime-=1;
        return;
    }
    for(i=start;i<n;i++){
        total=0;
        for(j=start;j<n-i-1;j++) {
            if ((P[j].bt > P[j + 1].bt )&& (P[j + 1].at <= total)) {
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
            total+=P[j].bt;
        }
    }
    P[start].remTime-=ts;
}
void RoundRobin(int n,int ts)
{
    int i,j=0,k=0,turn,wait,count=0;
    float totalWait=0,totalTurn=0;
    r=n-1;
    for(i=0;i<n;i++) {
        Q4[i] = JobQ[i];
        Q4[i].remTime=Q4[i].bt;
    }
    printf("\n\n\t\t\tRoundRobin\n");
    printf("+-----------------------------------------------------------------+\n");
    printf("|  PID  |  Priority  |   AT   |   BT   |   CT   |  TURN  |  WAIT  |\n");
    printf("|-----------------------------------------------------------------|\n");
    while((f<=r)&&(count<n))
    {
        for(i=f;i<=r;i++) {
            if (Q4[i].at <= j) {
                Q3[k] = dequeue(Q4,&f);
                k += 1;
            }
        }
        SJFroundRobin(Q3,tf,k,ts);
        if(Q3[tf].remTime==0)
        {
            Q3[tf].ct=j+1;
            turn=Q3[tf].ct-Q3[tf].at;
            wait=turn-Q3[tf].bt;
            printf("|   P%d  | %6d     | %4d   | %4d   | %4d   | %4d   | %4d   |\n",Q3[tf].pid,Q3[tf].priority,Q3[tf].at,Q3[tf].bt,Q3[tf].ct,turn,wait);
            totalTurn+=turn;
            totalWait+=wait;

            dequeue(Q3,&tf);
            //tf=tf+1;
            count++;
        }
        j++;
    }
    while(count<n){
        SJFroundRobin(Q3,tf,k,ts);
        if(Q3[tf].remTime==0)
        {
            Q3[tf].ct=j+1;
            turn=Q3[tf].ct-Q3[tf].at;
            wait=turn-Q3[tf].bt;
            printf("|   P%d  | %6d     | %4d   | %4d   | %4d   | %4d   | %4d   |\n",Q3[tf].pid,Q3[tf].priority,Q3[tf].at,Q3[tf].bt,Q3[tf].ct,turn,wait);
            totalTurn+=turn;
            totalWait+=wait;
            dequeue(Q3,&tf);
            //tf=tf+1;
            count++;
        }
        j++;
    }
    printf("+-----------------------------------------------------------------+\n");
    printf("Average TurnAround Time = %.2f\n",totalTurn/n);
    printf("Average Waiting Time = %.2f\n\n",totalWait/n);
}
int main()
{
    int n,i;
    Process P[20];
    printf("Enter the total nuber of processes: ");
    scanf(" %d",&n);
    for(i=0;i<n;i++){
        printf("Enter the arrivaltime, bursttime and priority of process%d\n",i+1);
        scanf("%d %d %d",&P[i].at,&P[i].bt,&P[i].priority);
        P[i].pid=i;
    }
    JOBQ(P,n);
    FPFS(n);
    SJF(JobQ,n);
    Priority(n);
    RoundRobin(n,1);
}