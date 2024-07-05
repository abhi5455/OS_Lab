#include<stdio.h>
#include<stdlib.h>
int n,request[25],temp[25],trackLimit,head;
int FCFS(){
    int i, seekTime=0, currPos=head;
    for(i=0;i<n;i++){
        seekTime += abs(request[i]-currPos);
        currPos=request[i];
    }
    printf("\nFCFS seek time: %d\n",seekTime);
    return seekTime;
}
int SSTF(){
    int i, j, seekTime=0, temp_var, index=0, currPos, leftPos,rightPos;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(temp[j]>temp[j+1]){
                temp_var=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_var;
            }
        }
    }
    for(i=0;i<n;i++){
        if(head<temp[i]){
            index=i;
            break;
        }
    }

    if(head>=temp[n-1]){
        seekTime+=abs(head-temp[0]);
    }
    else if(head<=temp[0]){
        seekTime+=abs(temp[n-1]-head);
    }
    else{
        currPos=head;
        rightPos=index;
        leftPos=index-1;
        for(i=0;i<n;i++){
            if(leftPos<0){
                seekTime+=abs(temp[rightPos]-currPos);
                currPos=temp[rightPos];
                rightPos++;
            }
            else if(rightPos>n-1){
                seekTime+=abs(currPos-temp[leftPos]);
                currPos=temp[leftPos];
                leftPos--;
            }
            else if((currPos-temp[leftPos])<(temp[rightPos]-currPos)){
                seekTime+=abs(currPos-temp[leftPos]);
                currPos=temp[leftPos];
                leftPos--;
            }
            else{
                seekTime+=abs(temp[rightPos]-currPos);
                currPos=temp[rightPos];
                rightPos++;
            }
        }
    }
    printf("SSTF seek time: %d\n",seekTime);
    return seekTime;
}
int SCAN(){
    int i, j, seekTime=0, temp_var, index=0;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(temp[j]>temp[j+1]){
                temp_var=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_var;
            }
        }
    }
    for(i=0;i<n;i++){
        if(head<=temp[i]){
            index=i;
            break;
        }
    }
    if(head>=temp[n-1]){
        seekTime+=abs(trackLimit-head);
        seekTime+= abs(trackLimit-temp[0]);
    }
    else if(head<=temp[0]){
        seekTime+=abs(temp[n-1]-head);
    }
    else{
        seekTime+=abs(trackLimit-head);
        seekTime+=(trackLimit-temp[0]);
    }
    printf("SCAN seek time: %d\n",seekTime);
    return seekTime;
}
int CSCAN(){
    int i, j, seekTime=0, currPos=head, temp_var,index=0;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(temp[j]>temp[j+1]){
                temp_var=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_var;
            }
        }
    }
    for(i=0;i<n;i++){
        if(head<=temp[i]){
            index=i;
            break;
        }
    }
    if(head>=temp[n-1]){
        seekTime+=abs(trackLimit-head);
        seekTime+= abs(trackLimit-0);
        if(head==temp[n-1]){
            seekTime+=abs(0-temp[n-2]);
        }
        else{
            seekTime+=abs(0-temp[n-1]);
        }
    }
    else if(head<=temp[0]){
        seekTime+=abs(temp[n-1]-head);
    }
    else{
        seekTime+=abs(trackLimit-head);
        seekTime+=trackLimit;
        seekTime+=temp[index-1];
    }
    printf("CSCAN seek time: %d\n",seekTime);
    return seekTime;
}
int LOOK(){
    int i, j, seekTime=0, currPos=head, temp_var,index=0;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(temp[j]>temp[j+1]){
                temp_var=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_var;
            }
        }
    }
    for(i=0;i<n;i++){
        if(head<=temp[i]){
            index=i;
            break;
        }
    }
    if(head>=temp[n-1]){
        seekTime+=abs(head-temp[0]);
    }
    else if(head<=temp[0]){
        seekTime+=abs(temp[n-1]-head);
    }
    else{
        seekTime+=abs(temp[n-1]-head);
        seekTime+=abs(temp[n-1]-temp[0]);
    }
    printf("LOOK seek time: %d\n",seekTime);
    return seekTime;
}
int CLOOK(){
    int i, j, seekTime=0, currPos=head, temp_var,index=0;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(temp[j]>temp[j+1]){
                temp_var=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_var;
            }
        }
    }
    for(i=0;i<n;i++){
        if(head<=temp[i]){
            index=i;
            break;
        }
    }
    if(head>=temp[n-1]){
        seekTime+=abs(head-temp[0]);
        if(head==temp[n-1]){
            seekTime+=abs(temp[0]-temp[n-2]);
        }
        else{
            seekTime+=abs(temp[0]-temp[n-1]);
        }
    }
    else if(head<=temp[0]){
        seekTime+=abs(temp[n-1]-head);
    }
    else{
        seekTime+=abs(temp[n-1]-head);
        seekTime+=abs(temp[n-1]-temp[0]);
        seekTime+=abs(temp[index-1]-temp[0]);
    }
    printf("CLOOK seek time: %d\n",seekTime);
    return seekTime;
}
int main(){
    int i;
    printf("Enter the number of requests: ");
    scanf(" %d",&n);
    printf("Enter the Request Sequence: ");
    for(i=0;i<n;i++){
        scanf("%d",&request[i]);
    }
    printf("Enter the disk size: ");
    scanf("%d",&trackLimit);
    trackLimit=trackLimit-1;
    printf("Enter the current head position: ");
    scanf("%d",&head);
    printf("\nDisk Size: (0 - %d)\n",trackLimit);
    for(i=0;i<n;i++){
        temp[i]=request[i];
        if((request[i]>trackLimit)||(head>trackLimit)||(head<0)){
            printf("\nIndexOutOfBound Exception!\n");
            return 1;
        }
    }
    printf("Request Sequence: ");
    for(i=0;i<n;i++){
        printf("%d ",temp[i]);
    }
    printf("\n");
    FCFS();
    SSTF();
    SCAN();
    CSCAN();
    LOOK();
    CLOOK();
    return 0;
}