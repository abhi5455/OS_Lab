#include<stdio.h>
typedef struct{
    int process;
    int partitionSize;

}Memory;
void display(Memory partition[30],int n)
{
    int i;
    printf("\n\t\t+");
    for(i=0;i<(6*n-1);i++)
        printf("-");
    printf("+\n     Partition: |");
    for(i=0;i<n;i++) {
        if (partition[i].process == -1) {
            printf("     |");
            continue;
        }
        printf(" %3d |", partition[i].process);
    }
    printf("\n\t\t+");
    for(i=0;i<(6*n-1);i++)
        printf("-");
    printf("+\n\t\t ");
    for(i=0;i<n;i++) {
        printf(" %3d  ", partition[i].partitionSize);
    }
    printf("\n\n");
}
void FirstFit(Memory* Partition,int n,int process[20],int m){
    int i,j,k=0,flag,Wait[m],internalFragment=0,externalFragment=0;
    for(i=0;i<m;i++){
        flag=0;
        for(j=0;j<n;j++){
            if(((Partition+j)->partitionSize >= process[i])&&((Partition+j)->process==-1)){
                (Partition+j)->process=process[i];
                flag=1;
                internalFragment+=(((Partition+j)->partitionSize)-process[i]);
                break;
            }
        }
        if(flag==0){
            Wait[k++]=process[i];
        }
    }
    printf("\nFIRST FIT\n---------");
    display(Partition,n);
    if(k==0)
        printf("     No Processes are waiting for Memory\n\n");
    else {
        printf("     Processes Waiting for Memory are:  ");
        for(i=0;i<k;i++)
            printf(" P(%d) ",Wait[i]);
    }
    printf("\nTotal Internal Fragmentation = %d\n",internalFragment);
    if(k!=0)
    {
        for(i=0;i<m;i++)
            if((Partition+i)->process==-1)
                externalFragment+=(Partition+i)->partitionSize;
    }
    printf("Total External Fragmentation = %d\n",externalFragment);
    printf("\n");
}
void BestFit(Memory* Partition,int n,int process[20],int m){
    int i,j,k=0,index,smallest,flag,Wait[m],internalFragment=0,externalFragment=0;
    for(i=0;i<n;i++)
        (Partition+i)->process=-1;
    for(i=0;i<m;i++){
        index=-1;
        smallest=0;
        flag=0;
        for(j=0;j<n;j++){
            if(((Partition+j)->partitionSize >= process[i])&&((Partition+j)->process==-1)){
                if(flag==0){
                    index=j;
                    smallest=(Partition+j)->partitionSize;
                }
                else if(smallest>(Partition+j)->partitionSize){
                    smallest=(Partition+j)->partitionSize;
                    index=j;
                }
                flag=1;
            }
        }
        if(index!=-1){
            (Partition+index)->process=process[i];
            internalFragment+=((Partition+index)->partitionSize-process[i]);
        }
        else{
            Wait[k++]=process[i];
        }
    }
    printf("\nBEST FIT\n--------");
    display(Partition,n);
    if(k==0)
        printf("     No Processes are waiting for Memory\n\n");
    else {
        printf("     Processes Waiting for Memory are:  ");
        for(i=0;i<k;i++)
            printf(" P(%d) ",Wait[i]);
    }
    printf("\nTotal Internal Fragmentation = %d\n",internalFragment);
    if(k!=0)
    {
        for(i=0;i<m;i++)
            if((Partition+i)->process==-1)
                externalFragment+=(Partition+i)->partitionSize;
    }
    printf("Total External Fragmentation = %d\n",externalFragment);
    printf("\n");
}
void WorstFit(Memory* Partition,int n,int process[20],int m){
    int i,j,k=0,index,largest,flag,Wait[m],internalFragment=0,externalFragment=0;
    for(i=0;i<n;i++)
        (Partition+i)->process=-1;
    for(i=0;i<m;i++){
        index=-1;
        largest=0;
        flag=0;
        for(j=0;j<n;j++){
            if(((Partition+j)->partitionSize >= process[i])&&((Partition+j)->process==-1)){
                if(flag==0){
                    index=j;
                    largest=(Partition+j)->partitionSize;
                }
                else if(largest<(Partition+j)->partitionSize){
                    largest=(Partition+j)->partitionSize;
                    index=j;
                }
                flag=1;
            }
        }
        if(index!=-1){
            (Partition+index)->process=process[i];
            internalFragment+=((Partition+index)->partitionSize-process[i]);
        }
        else{
            Wait[k++]=process[i];
        }
    }
    printf("\nWORST FIT\n---------");
    display(Partition,n);
    if(k==0)
        printf("     No Processes are waiting for Memory\n\n");
    else {
        printf("     Processes Waiting for Memory are:  ");
        for(i=0;i<k;i++)
            printf(" P(%d) ",Wait[i]);
    }
    printf("\nTotal Internal Fragmentation = %d\n",internalFragment);
    if(k!=0)
    {
        for(i=0;i<m;i++)
            if((Partition+i)->process==-1)
                externalFragment+=(Partition+i)->partitionSize;
    }
    printf("Total External Fragmentation = %d\n",externalFragment);
    printf("\n");

}
int main(){

    int n,m,i;
    printf("Enter the number of partitions: ");
    scanf("%d",&n);
    Memory Partition[n];
    for(i=0;i<n;i++) {
        printf("   Enter the Size of Partition %d: ", i + 1);
        scanf("%d",&Partition[i].partitionSize);
        Partition[i].process=-1;
    }
    printf("Enter the number of processes: ");
    scanf("%d",&m);
    int process[m];
    for(i=0;i<m;i++){
        printf("   Enter the Size of Process %d: ",i+1);
        scanf("%d",&process[i]);
    }
    FirstFit(Partition,n,process,m);
    BestFit(Partition,n,process,m);
    WorstFit(Partition,n,process,m);
    printf("\n");
}