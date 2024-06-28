#include<stdio.h>
int getseektime(int a, int b)
{
    if(a>b)
        return a-b;
    return b-a;
}
void copy(int arr[],int temp[],int n)
{
    for(int i=0;i<n;i++)
    {
        temp[i]=arr[i];
    }
}
void sort(int arr[],int n)
{
    int temp;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
int reqindex(int arr[],int p,int n)
{
    int i;
    for(int i=0;i<n;i++)
    {
        if(arr[i]>=p)
        {
            return i;
        }
    }
    return -1;
}
void fcfs(int arr[],int p,int n,int max)
    {
    printf("\nFCFS SCHEDULING\n");
    int seektime=0;
    printf("%d->",p);
    for(int i=0;i<n;i++)
    {
        seektime+=getseektime(arr[i],p);
        if(i != n-1)
        {
            printf("%d->",arr[i]);
        }
        else
        {
            printf("%d",arr[i]);
            p=arr[i];
        }
    }
    printf("The total head movementm in FCFS is: %d\n\n",seektime);
    }
int main()
{
    printf("DISK SCEDULING\n");
    int max,n,p;
    printf("Enter the track limit of the disk:");
    scanf("%d",&max);
    printf("Enter the number of requests:");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the numbers:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("Enter the current position of the track:");
    scanf("%d",&p);
    fcfs(arr,p,max,n);
    return 0;

}