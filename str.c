#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void GenerateString(int n, char* str);  

int main()
{
	int n = 0;
	printf("n = ");
	scanf("%d", &n);
	char* str = (char*)malloc((1<<n)*sizeof(char));
	GenerateString(n, str);
	free(str);
	return 0;
}
void GenerateString(int n, char* str)
{
	int i = 0;
	str[0] = 'a';
	for(i = 1; i < n; i++)
	{
		str[strlen(str)] = str[0] + i;
		strncpy(str + strlen(str), str, strlen(str) - 1);
		
	}
	printf("%s", str);
}
