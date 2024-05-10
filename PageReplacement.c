#include<stdio.h>
typedef struct{
    int PageN;
    int lastUsed;
    int freq;
}Frame;
void display(Frame pages[30],int n)
{
    int i;
    printf("\n\t  +");
    for(i=0;i<(6*n-1);i++)
        printf("-");
    printf("+\n  Frames: |");
    for(i=0;i<n;i++) {
        if (pages[i].PageN == -1) {
            printf("     |");
            continue;
        }
        printf("%3d  |", pages[i].PageN);
    }
    printf("\n\t  +");
    for(i=0;i<(6*n-1);i++)
        printf("-");
    printf("+");
}
void FIFS(Frame* Frames,int Frame_Size,int Pages[30],int n)
{
    int i,j;
    printf("\n\n\t\t FIFS\n");
    int pageFault=0,index=-1;
    for(i=0;i<Frame_Size;i++)
        (Frames+i)->PageN=-1;
    display(Frames,Frame_Size);
    for(i=0;i<n;i++){
        int pageFound=0;
        for(j=0;j<Frame_Size;j++){
            if((Frames+j)->PageN==Pages[i]){
                pageFound=1;
            }
        }
        if(!pageFound){
            pageFault++;
            index=(index+1)%Frame_Size;
            (Frames+index)->PageN=Pages[i];
        }
        display(Frames,Frame_Size);
    }
    printf("\nNo of PageFaults =%3d ",pageFault);
    printf("\t PageFault Ratio = %.2f",((float)pageFault/n));
    printf("\nNo of PageHits =%3d ",n-pageFault);
    printf("\t PageHit Ratio = %.2f\n\n",((float)(n-pageFault)/n));
}
void LRU(Frame* Frames,int Frame_Size,int Pages[30],int n){
    int i,j;
    printf("\n\t\t LRU\n");
    int pageFault=0;
    for(i=0;i<Frame_Size;i++) {
        (Frames + i)->PageN = -1;
        (Frames + i)->lastUsed = 0;
    }
    display(Frames,Frame_Size);
    int z=1;
    for(i=0;i<n;i++){
        int pageFound=0;
        for(j=0;j<Frame_Size;j++){
            if((Frames+j)->PageN==Pages[i]){
                pageFound=1;
                (Frames+j)->lastUsed=z;
                z++;
                break;
            }
        }
        if(!pageFound){
            pageFault++;
            int min=0;
            for(j=1;j<Frame_Size;j++){
                if((Frames+j)->lastUsed<(Frames+min)->lastUsed){
                    min=j;
                }
            }
            (Frames+min)->PageN=Pages[i];
            (Frames+min)->lastUsed=z;
            z++;
        }
        display(Frames,Frame_Size);
    }
    printf("\nNo of PageFaults =%3d ",pageFault);
    printf("\t PageFault Ratio = %.2f",((float)pageFault/n));
    printf("\nNo of PageHits =%3d ",n-pageFault);
    printf("\t PageHit Ratio = %.2f\n\n",((float)(n-pageFault)/n));

}
void LFU(Frame* Frames,int Frame_Size,int Pages[30],int n){
    int i,j;
    printf("\n\t\t LFU\n");
    int pageFault=0;
    for(i=0;i<Frame_Size;i++) {
        (Frames + i)->PageN = -1;
        (Frames + i)->freq = 0;
    }
    display(Frames,Frame_Size);
    int index=0;
    for(i=0;i<n;i++){
        int pageFound=0;
        for(j=0;j<Frame_Size;j++){
            if((Frames+j)->PageN==Pages[i]){
                pageFound=1;
                (Frames+j)->freq+=1;
                break;
            }
        }
        if(!pageFound){
            pageFault++;
            int min=index;
            for(j=0;j<Frame_Size;j++){
                if((Frames+index)->freq<(Frames+min)->freq){
                    min=index;
                }
                index=(index+1)%Frame_Size;
            }
            (Frames+min)->PageN=Pages[i];
            (Frames+min)->freq=1;
            index=(min+1)%Frame_Size;
        }
        display(Frames,Frame_Size);
    }
    printf("\nNo of PageFaults =%3d ",pageFault);
    printf("\t PageFault Ratio = %.2f",((float)pageFault/n));
    printf("\nNo of PageHits =%3d ",n-pageFault);
    printf("\t PageHit Ratio = %.2f\n\n",((float)(n-pageFault)/n));

}
int main()
{
    int Frame_Size,n,i;
    printf("Enter the size of Frame: ");
    scanf("%d",&Frame_Size);
    Frame Frames[Frame_Size];
    printf("Enter the Number of pages: ");
    scanf("%d",&n);
    int Pages[n];
    printf("Enter the Page Numbers: ");
    for(i=0;i<n;i++)
        scanf("%d",&Pages[i]);

    printf("\nAvailable Pages are: ");
    for(i=0;i<n;i++)
        printf("%3d",Pages[i]);

    FIFS(Frames,Frame_Size,Pages,n);
    LRU(Frames,Frame_Size,Pages,n);
    LFU(Frames,Frame_Size,Pages,n);
    return 0;
}