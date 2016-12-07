#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/types.h>  
#include <signal.h> 
#include <string.h> 

pid_t ppid; 
char sendline[] = "Happy new year! :-)\n"; 
char recvline[255]; 
int pos = 0; 

void receiver(int signal);
void sender();

int main() 
{ 
	signal(SIGUSR1, receiver); 
	signal(SIGUSR2, receiver); 
	signal(SIGINT, sender); 
	ppid = getpid(); 
	pid_t pid = fork(); 
	if (pid != 0) 
	{ 
		ppid = pid; 
		sender(); 
	} 
	while(1);
	return 0; 
}

void receiver(int signal) 
{
	if (signal == SIGUSR2) 
		recvline[pos / 8] = recvline[pos / 8] | (1 << (pos % 8)); 
	kill(ppid, SIGINT); 
	pos ++; 
	if (((pos - 1) / 8) == strlen(sendline)) 
		printf("%s\n", recvline); 
} 

void sender() 
{ 
	pos++; 
	if ((sendline[pos / 8] & (1 << (pos - 1) % 8)) == 0)
		kill(ppid, SIGUSR1); 
	else
		kill(ppid, SIGUSR2); 
	if (((pos - 1) / 8) == strlen(sendline)) 
		exit(0); 
} 
