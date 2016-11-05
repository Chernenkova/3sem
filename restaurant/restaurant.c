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

#define TABLE_LIMIT 10	

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

struct dishes washer[50];
struct durty_dishes durt;


int msqid; 	
struct mymsgbuf								//structure of messages(out)
{
	long mtype;
	struct 
	{	
		struct durty_dishes durt;
	} info;
} mybuf;

int semid; 	
struct sembuf mysem;


void wash (struct durty_dishes durt, int w);

int main()
{
	FILE* f1 = fopen("wash.txt", "r");	//person, who wash the dishes	
	FILE* f3 = fopen("durt.txt", "r");	//durty dishes
	int w = 0, i = 0;
	while (1)										
	{
		if (fscanf(f1, "%s : %d", washer[w].type, &washer[w].time) == EOF)
			break;
		w++;
	}
	//printf("Washer:\n");
	//for (i = 0; i < w; i++)
	//	printf("%s %d\n", washer[i].type, washer[i].time);
	//printf("\n");
	
	
	
									//semafors
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
    mysem.sem_op = TABLE_LIMIT;
    mysem.sem_flg = 0;
    mysem.sem_num = 0;
    semop(semid , &mysem, 1);
	
									
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
    

  
	mybuf.mtype = 1;
    
    
	
	while(1)									//WORK
	{
		if (fscanf(f3, "%s : %d", durt.type, &durt.number) == EOF)
			break;
		
		for (i = 0; i < durt.number; i++)
		{
			wash(durt, w);
			strncpy(mybuf.info.durt.type, durt.type, sizeof(durt.type));
			if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.info), 0) < 0) 	//sending of the message
			{
			  printf("Can\'t send message to queue\n");
			  msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
			  exit(-1);
			}	
		}
	}
	strncpy(mybuf.info.durt.type, "finish", sizeof("finish"));
	msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.info), 0);
	printf("Dobbi is free!!!\n");
	fclose(f1);
	fclose(f3);
	return 0;
}

void wash (struct durty_dishes durt, int w)
{
	int j = 0;    
	printf("Begin to wash %s\n", durt.type);
	for (j = 0; j < w; j++)
		if (strcmp(washer[j].type, durt.type) == 0)
			break;		
	sleep(washer[j].time);
	mysem.sem_op = -1;
    semop(semid , &mysem, 1);
	printf("Finish to wash %s\n", durt.type);
	printf("\n");
	
}
