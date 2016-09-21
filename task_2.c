#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
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
	    wait(status);
	    printf("The child of %d has finished.\n", getppid());
    	    exit(0);
	}
	printf("Process: %d, parent:  %d\n", getpid(), getppid());
    }
    return 0;
}
