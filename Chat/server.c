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

int main()
{
	struct User
	{
		int ip, port;
		char nick[20];
	};
	struct User* users = (struct User*)malloc(sizeof(struct User));

	int sockfd;
	int clilen, n, i, j, flag, k;
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
	else
	{
		printf("Sock fd: %d\n\n", sockfd);
	}

	if (bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(1);
	}

	while (1)
	{
		clilen = sizeof(cliaddr);
		if ((n = recvfrom(sockfd, line, 999, 0, (struct sockaddr*)&cliaddr, &clilen)) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(1);
		}
		if (strncmp("My nick is ", line, 11) == 0)
		{
			number++;
			users = realloc (users, number * sizeof(struct User));
			users[number - 1].ip = (int)cliaddr.sin_addr.s_addr;
			users[number - 1].port = (int)cliaddr.sin_port;
			for (i = 11; i < strlen(line) - 1; i++)
				users[number - 1].nick[i-11] = line[i];
			printf("New client (%d): %s\nYou are welcome!\nTotal %d clients\n\n", users[number - 1].port, users[number - 1].nick, number);
			for (i = 0; i < number; i++)
			{
				cliaddr.sin_addr.s_addr = users[i].ip;
				cliaddr.sin_port = users[i].port;
				
				for (i = 0; i < number; i++)
				{
					strcpy(line2, "New client: ");
					strcat(line2, users[number - 1].nick);
					strcat(line2, "\n");
					cliaddr.sin_addr.s_addr = users[i].ip;
					cliaddr.sin_port = users[i].port;
					if (sendto(sockfd, line2, strlen(line2) + 1, 0, (struct sockaddr*)&cliaddr, clilen) < 0)
					{
						perror(NULL);
						close(sockfd);
						exit(1);
					}
				}
			}
		}
		else
		{
			flag = -5;
			for(j = 0; j < number; j++)
			{
				if ((strncmp(line, users[j].nick, strlen(users[j].nick)) == 0) && (line[strlen(users[j].nick)] == '#'))
				{
					flag = j;
					break;
				}
			}
			if (flag == -5)
			{
				for (i = 0; i < number; i++)
					if (((int)cliaddr.sin_addr.s_addr == users[i].ip) && ((int)cliaddr.sin_port == users[i].port))
					{
						k = i;	
						break;
					}
					
					
				printf("%s says: %srecieve %d byte\n\n", users[i].nick, line, n);
				for (i = 0; i < number; i++)
				{
					if (i == k)
						continue;
					else	
					{
						strcpy(line2, users[k].nick);
						strcat(line2, " says: ");
						strcat(line2, line); 
						cliaddr.sin_addr.s_addr = users[i].ip;
						cliaddr.sin_port = users[i].port;
						if (sendto(sockfd, line2, strlen(line2) + 1, 0, (struct sockaddr*)&cliaddr, clilen) < 0)
						{
							perror(NULL);
							close(sockfd);
							exit(1);
						}
					}
				}
			}
			else
			{
				for (i = 0; i < number; i++)
					if (((int)cliaddr.sin_addr.s_addr == users[i].ip) && ((int)cliaddr.sin_port == users[i].port))
					{
						k = i;	
						break;
					}
				strcpy(line2, users[k].nick);
				strcat(line2, " says (private): ");
				j = strlen(line2);
				for (i = strlen(users[flag].nick) + 1; i < strlen(line)+1; i++)
					line2[j + i - strlen(users[flag].nick) - 1] = line[i];
				strcat(line2, "\0");
				cliaddr.sin_addr.s_addr = users[flag].ip;
				cliaddr.sin_port = users[flag].port;
				if (sendto(sockfd, line2, strlen(line2) + 1, 0, (struct sockaddr*)&cliaddr, clilen) < 0)
					{
						perror(NULL);
						close(sockfd);
						exit(1);
					}
			}
		}
	}
	return 0;
}
