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

#define K 3

void itoa(int n, char s[]);

int main()
{
	struct User
	{
		int ip, port;
		char nick[20];
	};
	struct User* users = (struct User*)malloc(sizeof(struct User));

	char byte[5];
	int sockfd, s = 0;
	int array[100];
	int clilen, n, i, a = 0, b = 0, j = 0, x = 0;
	int number = 0;		//number of clients
	char line[1000], line2[1027];
	struct sockaddr_in servaddr, cliaddr;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(51000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror(NULL);
		exit(1);
	}


	if (bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(1);
	}



	for (i = 0; i < K; i++)
	{
		clilen = sizeof(cliaddr);
		if ((n = recvfrom(sockfd, line, 999, 0, (struct sockaddr*)&cliaddr, &clilen)) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(1);
		}
		
			number++;
			users = realloc (users, number * sizeof(struct User));
			users[number - 1].ip = (int)cliaddr.sin_addr.s_addr;
			users[number - 1].port = (int)cliaddr.sin_port;
			for (j = 11; j < strlen(line) - 1; j++)
				users[number - 1].nick[j-11] = line[j];
			printf("New client!\nYou are welcome!\nTotal %d clients\n\n", number);
			
			strcpy(line2, "OK!\n");
			if (sendto(sockfd, line2, strlen(line2) + 1, 0, (struct sockaddr*)&cliaddr, clilen) < 0)
			{
				perror(NULL);
				close(sockfd);
				exit(1);
			}	
	}
	FILE* f1 = fopen("array.txt", "r");
	int w = 0;
	while (1)										
	{
		if (fscanf(f1, "%d ", &array[w]) == EOF)
			break;
		w++;
	}
	fclose(f1);
	
	/*
	for (i = 0; i < w; i++)
		printf("%d ", array[i]);
	printf("\n\n");
	*/

	strcpy(line2, "\n");
	a = w / K;
	b = w - a * K;
	
	for (i = 0; i < K; i++)
	{
		for (j = 0; j < a; j++)
		{
			itoa(array[x++], byte);
			if (j == 0)
				strcpy(line2, byte);
			else
				strcat(line2, byte);
			if (j != a - 1)
				strcat(line2, " ");
		}
		
		if (b != 0)
		{
			strcat(line2, " ");
			itoa(array[x++], byte);
			strcat(line2, byte);
			b--;
		}
		//printf("%s\n", line2);
		cliaddr.sin_addr.s_addr = users[i].ip;
		cliaddr.sin_port = users[i].port;
		if (sendto(sockfd, line2, strlen(line2) + 1, 0, (struct sockaddr*)&cliaddr, clilen) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(1);
		}
		strcpy(line2, "\n");
		if ((n = recvfrom(sockfd, line, 1000, 0, (struct sockaddr*) NULL, NULL)) < 0)
			{
				perror(NULL);
				close(sockfd);
				exit(1);
			}
		//printf("%s\n", line);	
		s = s + atoi(line);	
		
	}
	printf("result: %d\n", s);
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



