#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define LAST_MESSAGE 255 

int main()
{
  /* IPC дескриптор для очереди сообщений */
  int msqid; 
  

  /* Имя файла, использующееся для генерации ключа.
     Файл с таким именем должен существовать в текущей директории */
  char pathname[] = "ex0.c"; 

  /* IPC ключ */
  key_t key; 

  /* Cчетчик цикла и длина информативной части сообщения */
  int len, maxlen = 81; 

  /* Ниже следует пользовательская структура для сообщения */
  struct mymsgbuf
  {
    long mtype;
    struct {
		int a, b, c;
		pid_t mypid;
	} info;
  } mybuf;
  

  /* Генерируем IPC ключ из имени файла 09-1a.c в текущей директории
  и номера экземпляра очереди сообщений 0. */
  if ((key = ftok(pathname, 0)) < 0)
  {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  /* Пытаемся получить доступ по ключу к очереди сообщений, если она существует,
  или создать ее, если она еще не существует, с правами доступа
  read & write для всех пользователей */
  if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
  {
    printf("Can\'t get msqid\n");
    exit(-1);
  }
	
	mybuf.info.mypid = getpid();
  /* Посылаем в цикле 5 сообщений с типом 1 в очередь сообщений, идентифицируемую msqid.*/
  while(1)
  {
    /* Сначала заполняем структуру для нашего сообщения и определяем длину информативной части */
    mybuf.mtype = 1;
    scanf("%d %d", &mybuf.info.a, &mybuf.info.b);

    /* Отсылаем сообщение. В случае ошибки сообщаем об этом и удаляем очередь сообщений из системы. */
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.info), 0) < 0)
    {
      printf("Can\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
      exit(-1);
    }
    
    if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, getpid(), 0)) < 0)
    {
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }
    mybuf.mtype = 1;
    
    printf("%d * %d = %d\n",mybuf.info.a, mybuf.info.b, mybuf.info.c);

  }

  /* Отсылаем сообщение, которое заставит получающий процесс прекратить работу, с типом LAST_MESSAGE и длиной 0 */
  mybuf.mtype = LAST_MESSAGE;
  len = 0;

  if (msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0) < 0)
  {
    printf("Can\'t send message to queue\n");
    msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
    exit(-1);
  }
  return 0;
} 
