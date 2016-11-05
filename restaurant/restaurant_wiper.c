#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/sem.h>



struct dishes
{
	char type[10];
	int time;
};


struct durty_dishes
{
	char type[10];
	int number;
};

struct dishes wiper[50];
struct durty_dishes durt;

int semid; 	
struct sembuf mysem;


int msqid; 	
struct mymsgbuf								//structure of messages(in)
{
	long mtype;
	struct 
	{
		struct durty_dishes durt;
	} info;
} mybuf;

struct mymsgbuf2								//structure of messages(out)
{
	long mtype;
	int k;
} mybuf2;



void wipe (struct durty_dishes durt, int w);

int main()
{
	FILE* f2 = fopen("wipe.txt", "r");	//person, who wipe the dishes
	int w = 0;
	while (1)
	{
		if (fscanf(f2, "%s : %d", wiper[w].type, &wiper[w].time) == EOF)
			break;
		w++;
	}
	//int i = 0;												
	//printf("Wiper:\n");
	//for (i = 0; i < w; i++)
	//	printf("%s %d\n", wiper[i].type, wiper[i].time);
	//printf("\n");	
	
	
	const char pathname[] = "s08e01a.c"; 
    key_t key1;
    if ((key1 = ftok(pathname , 0)) < 0 ) 
    {
        printf("Can`t generate key\n");
        exit(-1);
    }
    if ((semid = semget(key1, 1, 0666 | IPC_CREAT)) < 0) 
    {
        printf("Can`t get semid\n");
        exit(-1);
    }
	
	
	
	char pathname2[] = "ex0.c"; 		//for messages
	key_t key; 
	if ((key = ftok(pathname2, 0)) < 0)
	{
		printf("Can\'t generate key\n");
		exit(-1);
	}
	if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
	{
		printf("Can\'t get msqid\n");
		exit(-1);
	}
	
    while (1)				//WORK
	{	
		if (msgrcv(msqid, (struct msgbuf *)&mybuf, sizeof(mybuf.info), 1, 0) < 0)
		{
			printf("Can\'t receive message from queue\n");
			exit(-1);
		}
		//printf("%s\n", mybuf.info.durt.type);
		if (strcmp(mybuf.info.durt.type, "finish") == 0)
			break;	
		//msgsnd(msqid, (struct msgbuf *) &mybuf2, sizeof(mybuf2.k), 0);
		mysem.sem_op = 1;
		semop(semid , &mysem, 1);
		wipe (mybuf.info.durt, w);
	} 
	printf("Dobbi is free!!!\n");
	fclose(f2);
	return 0;
}

void wipe (struct durty_dishes durt, int w)
{
	int j = 0;    
	printf("Begin to wipe %s\n", durt.type);
	for (j = 0; j < w; j++)
		if (strcmp(wiper[j].type, durt.type) == 0)
			break;		
	sleep(wiper[j].time);	
	printf("Finish to wipe %s\n", durt.type);
	printf("\n");
}
