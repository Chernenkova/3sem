#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void itoa(int n, char s[]);

int main(int argc, char** argv)
{
	int array[50];
	int sockfd, i = 0, j = 0;
	char* istr;
	int n;
	char sendline[1000], recvline[1000];
	struct sockaddr_in servaddr, cliaddr;

	if (argc != 2)
	{
		printf("Usage: ./a.out <IP address>\n");
		exit(1);
	}
	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror(NULL);
		exit(1);
	}

	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(0);										//port
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);						//ip

	if (bind(sockfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr)) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(51000);
	if (inet_aton(argv[1], &servaddr.sin_addr) == 0)
	{
		printf("Invalid IP address\n");
		close(sockfd);
		exit(1);
	}
	
	
		printf("Nick name -> ");
		fgets(sendline, 20, stdin);
		printf("\n");
		strcat(recvline, "My nick is ");
		strcat(recvline, sendline);
		strcpy(sendline, recvline);
		if (sendto(sockfd, sendline, strlen(sendline) + 1, 0, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(1);
		}

		if ((n = recvfrom(sockfd, recvline, 1000, 0, (struct sockaddr*) NULL, NULL)) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(1);
		}
		printf("%s\n", recvline);
	
	
		i = 0;
	
		while(1)
		{
			if ((n = recvfrom(sockfd, recvline, 1000, 0, (struct sockaddr*) NULL, NULL)) < 0)
			{
				perror(NULL);
				close(sockfd);
				exit(1);
			}
			printf("recv: %s\n", recvline);	
			istr = strtok(recvline, " ");
			while(istr != NULL)
			{
				array[i++] = atoi(istr);
				istr = strtok(NULL, " ");
			}
			int s = 0;
			
			/*for(j = 0; j < i; j++)
				printf("%d ", array[j]);
			printf("\n\n");
			* */
			for(j = 0; j < i; j++)
				s = s + array[j];
			//printf("sum: %d\n", s);
			itoa(s, sendline);
			printf("send: %s\n", sendline);	
			if (sendto(sockfd, sendline, strlen(sendline) + 1, 0, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
			{
				perror(NULL);
				close(sockfd);
				exit(1);
			}
		}	
	close(sockfd);
	return 0;
}
void itoa(int n, char s[])
{
	int i = 0, j = 0;
	char c;
	while ((n / 10) > 0)
	{
		s[i++] = n % 10 + '0';
		n = n / 10;
	}
	
	s[i++] = n + '0';
	s[i] = '\0';
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
