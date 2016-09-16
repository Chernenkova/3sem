#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  

int main()
{
	printf("User: %d\n", getuid());
	printf("Group: %d\n", getgid());
	return 0;
}

