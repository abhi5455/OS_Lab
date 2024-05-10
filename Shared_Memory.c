#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define key 0x131
#define SIZE 50

typedef struct {
    char str[SIZE];
    char name[SIZE];
} MessageBlock;
typedef struct {
    MessageBlock message[20];
    int f;
    int r;
} MessageBox;

MessageBox *msg;
char username[SIZE];

void addMessage(MessageBlock item) {
    if (msg->f == -1) {
        msg->f = 0;
    }
    msg->r = (msg->r + 1) % SIZE; //Circular Queue
    msg->message[msg->r] = item;
}

MessageBlock getMsg() {
    MessageBlock item = msg->message[msg->f];
    msg->f = ((msg->f) + 1) % SIZE;
    if ((msg->f) == ((msg->r) + 1) % SIZE) {
        msg->f = msg->r = -1;
    }
    return item;
}

void *msgReceiver(void *args) {
    while (1) {
        MessageBlock chat;

        while (msg->f == -1);

        if (strcmp(msg->message[msg->f].name, username) == 0) {
            continue;
        }
        chat = getMsg();
        printf("\n%s  -from user %s\n", chat.str, chat.name);

    }
}

int main() {
    int shmid;
    pthread_t Rthread;
    shmid = shmget(key, sizeof(MessageBox), 0666 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    msg = (MessageBox *) shmat(shmid, NULL, 0666);
    msg->f = -1;
    msg->r = -1;
    printf("User Name: ");
    fgets(username, sizeof(username), stdin);
    //
    username[strcspn(username, "\n")] = '\0';

    int thd_sts = pthread_create(&Rthread, NULL, msgReceiver, NULL);
    if (thd_sts != 0) {
        perror("Thread");
        exit(1);
    }

    while (1) {
        char chat[SIZE];
        MessageBlock tempMsg;

        printf("Write Message: ");
        fgets(chat, sizeof(chat), stdin);
        chat[strcspn(chat, "\n")] = '\0';

        strncpy(tempMsg.name, username, SIZE - 1);
        tempMsg.name[SIZE - 1] = '\0';
        strncpy(tempMsg.str, chat, SIZE - 1);
        tempMsg.str[SIZE - 1] = '\0';
        addMessage(tempMsg);
    }
    pthread_join(Rthread, NULL);
}