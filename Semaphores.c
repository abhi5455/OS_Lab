#include<stdio.h>
#include<pthread.h>
#define SIZE 20

int S[SIZE],f=-1,r=-1,num=0,wait=0;

void enqueue(int item)
{
    if(f==-1){
        f=0;
    }
    r=(r+1)%SIZE;
    S[r]=item;
}
int dequeue()
{
    int item = S[f];
    f = (f+1) % SIZE;
    if(f == (r+1) % SIZE)
        f=r=-1;
    return item;
}
void* ProducerFun(void* args)
{
    while(num<20) {
        num=num+1;
        while(((r+1) % SIZE == f)|| wait==1);
        printf("%d\t\t\t-Thread1\n",num);
        enqueue(num);
        wait=1;
    }
}
void* ConsumerFun(void* args)
{
    while(1) {
        while(r==-1 || wait==0);
        int x = dequeue();
        if(x%2==0)
            printf("%d is an Even Number\t-Thread2\n",x);
        else
            printf("%d is an Odd Number\t-Thread2\n",x);
        wait = 0;
    }
}
int main() {
    pthread_t Producer,Consumer;
    int producer_stat = pthread_create(&Producer, NULL, ProducerFun, (void *) NULL);
    int consumer_stat = pthread_create(&Consumer, NULL, ConsumerFun, (void *) NULL);

    if (producer_stat != 0 || consumer_stat != 0) {
        perror("Threads error");
        exit(1);
    }
    pthread_join(Producer, NULL);
    pthread_join(Consumer, NULL);
    return 0;
}