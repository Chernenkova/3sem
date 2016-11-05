#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/sem.h>
#include <pthread.h>

#define LAST_MESSAGE 255 
#define N 2
int msqid, semid;
struct mymsgbuf
  {
    long mtype;
    struct {
		int a, b, c;
		pid_t mypid;
	} info;
  } mybuf;
  struct sembuf mysem;

void *mythread(void *dummy)
{
	mysem.sem_op = -1;
	semop(semid, &mysem, 0);
	printf("start %d * %d\n", mybuf.info.a, mybuf.info.b);
	mybuf.info.c = mybuf.info.a * mybuf.info.b;
	sleep(5);
	mybuf.mtype = mybuf.info.mypid;
	
	if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.info), 0) < 0)
    {
      printf("Can\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
      exit(-1);
    }
    mysem.sem_op = 1;
    semop(semid, &mysem, 0);
    printf("finish\n");
	return NULL;
}

int main()
{
	pthread_t thid;

  char pathname[] = "ex0.c"; 

  key_t key;
  int len; 

  if((key = ftok(pathname, 0)) < 0)
  {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
  {
    printf("Can\'t get msqid\n");
    exit(-1);
  }
  
  if((semid = semget(key,1, 0666 | IPC_CREAT)) < 0)
  {
    printf("Can\'t get semid\n");
    exit(-1);
  }

	mysem.sem_op = -1;
	mysem.sem_flg = 0;
	mysem.sem_num = N;
	
  while (1)
  {
    if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, sizeof(mybuf.info), 1, 0)) < 0)
    {
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }


    int result = pthread_create(&thid, (pthread_attr_t *) NULL, mythread, NULL);
	if(result != 0)
	{
		printf ("Error on thread create, return value = %d\n", result);
		exit(-1);
	}
  } 
  return 0;
} 
