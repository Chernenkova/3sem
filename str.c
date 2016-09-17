#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void GenerateString(int n, char* str);  

int main()
{
	int n = 0;
	printf("n = ");
	scanf("%d", &n);
/*
 * ставьте пробелы вокруг бинарных операторов
 * char* str = (char*)malloc((1 << n) * sizeof(char));
 */
	char* str = (char*)malloc((1<<n)*sizeof(char));
	GenerateString(n, str);
/*
 * если вы в функцию передаёте указатель на массив, куда надо записать результат, а ф-я
 * называется Generete, а не GenerateAndPrint, то лучше вывести результат вне ф-и
 */
  printf("%s", str);
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
}
