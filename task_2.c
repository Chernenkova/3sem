#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

/*
 * number of nodes?
 */
#define NUMBER_OF_TREES 10

int main()
{
    int  i = 0;
    int* status;
    for(i = 0; i < NUMBER_OF_TREES; i++)
    {
	pid_t pid = fork();
	if(pid != 0)
	{
/*
 * FIXIT:
 * когда ф-я принимает указатель на какие-то данные, то они вероятно выходные. как раз для wait статус завершения дочернего процесса записывается в участок памяти,
 * но который ссылается переданный указатель. т.е. обязательно предполагается, что память под него выделена либо на стеке, либо в куче.
 * у вас же status - некая неинициализированная переменная ...
 */
	    wait(status);
	    printf("The child of %d has finished.\n", getppid());
    	    exit(0);
	}
	printf("Process: %d, parent:  %d\n", getpid(), getppid());
    }
    return 0;
}
