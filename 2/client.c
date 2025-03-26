#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define LAST_MESSAGE 255

int main(void)
{
    int msqid;
    char pathname[] = "server.c"; 
                                   
    key_t key;                     
    int len;                    
    struct mymsgbuf                
    {
        long mtype;
        char infotext[81];

    } mybuf = {0, {}};
    int maxlen = sizeof(mybuf.infotext);
    if ((key = ftok(pathname, 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

  
    mybuf.mtype = 1;
    strcpy(mybuf.infotext, "SYN");
    if (msgsnd(msqid, (struct msgbuf *)&mybuf, strlen(mybuf.infotext) + 1, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
        exit(-1);
    }
    printf("Client sent %s\n", mybuf.infotext);

    if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, 2, 0)) < 0)
    {
        printf("Can\'t receive message from queue\n");
        exit(-1);
    }
    printf("Client get %s from server\n", mybuf.infotext);

    mybuf.mtype = 1;
    strcpy(mybuf.infotext, "ACK");
    if (msgsnd(msqid, (struct msgbuf *)&mybuf, strlen(mybuf.infotext) + 1, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
        exit(-1);
    }
    printf("Client sent %s\n", mybuf.infotext);

 

    mybuf.mtype = LAST_MESSAGE;

    if (msgsnd(msqid, (struct msgbuf *)&mybuf, 0, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
        exit(-1);
    }

    return 0;
}
