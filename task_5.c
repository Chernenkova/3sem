#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

/*
 * та же беда, что и у Егора Бригиды (почти 1 в 1 код): ваша программа работает только для одного конкретного набора входных команд.
 * Задание не засчитано.
 */
int main()
{
    FILE *f = fopen("test.txt", "r"); 
    int number_of_lines = 0, seconds = 0, i = 0;
    int* status;
    char string1[10], string2[10], string3[10];

    fscanf(f, "%d\n", &number_of_lines);

    //the first
    fscanf(f, "%s ", string1); 
    fscanf(f, "%s ", string2);
    fscanf(f, "%d", &seconds);
    pid_t first = fork();
    wait(status);
    if (first == 0)
    {
        sleep(seconds);
        execlp(string1, string1, string2, NULL);
    }
    
    printf("\n");

    //the second
    fscanf(f, "%s ", string1);
    fscanf(f, "%d", &seconds);
    pid_t second = fork();
    wait(status);
    if(second == 0)
    {
	sleep(seconds);
	execlp(string1, string1, NULL);
    }

    printf("\n");

    //the third
    fscanf(f, "%s ", string1);
    fscanf(f, "%s ", string2);
    fscanf(f, "%s ", string3);
    strcat(string2, string3);
    fscanf(f, "%d", &seconds);
    pid_t third = fork();
    wait(status);
    if(third == 0)
    {
	sleep(seconds);
	execlp(string1, string1, string2, NULL);
    }

    fclose(f);
    return 0;
}
