#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define n 255

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount);

int main () 
{	
	char string[n], delimiters[n];
	int i = 0, tokensCount = 0;
	char** tokens = (char**)malloc(n * sizeof(char));
	for (i = 0; i < n; i++)
		tokens[i] = (char*)malloc(n * sizeof(char));
	
	gets(string);
	gets(delimiters);
	
	Split(string, delimiters, &tokens, &tokensCount);
	
	for (i = 0; i < tokensCount; i++)
		printf("%s\n",tokens[i]);
	
	return 0;
}

void Split(char* string, char* delimiters, char*** tokens, int* tokensCount)
{
	char* p = strtok(string, delimiters);
	while (p != NULL) 
	{
		strcpy((*tokens)[(*tokensCount)++], p);
 		p = strtok(NULL, delimiters); 
	}
}
