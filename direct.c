#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define N 2		//depth
#define FILE "ex0.c"

//char s[100];

int k = 0;

void Find (char* file, char* direct, int depth);

int main()
{
	char* path = (char*)malloc(1000);
	path[0] = '.';
	Find(FILE, path, N);
	free(path);
	return 0;
}

void Find (char* file, char* direct, int depth)
{
	if (depth -- < 0) 
		return;
	DIR *dir = opendir(direct);
	struct dirent *abc;
	struct stat buff;
	char* s = (char*)malloc(1000);
	//char s[400];
	while((abc = readdir(dir)) != NULL)
	{
		s[0] = '\0';
		strcpy(s, direct);
		strcat(s, "/");
		strcat(s, abc -> d_name);
		stat(s, &buff);
		//printf("%s\n", s);
		if (S_ISDIR(buff.st_mode))
		{
			if((strcmp(abc -> d_name, "..")) && (strcmp(abc -> d_name, ".")))
			{
				Find(file, s, depth);			
			}
		}
		else
		{
			if (strcmp(abc -> d_name, file)  == 0)
			{
				strcat(s, "\n");
				k = 1;
				printf("file have been found: %s\n", s);
				return;
			}
		}
	}
	if ((depth == N - 1) && (k == 0))
		printf("file haven't been found\n");
	return;
}
