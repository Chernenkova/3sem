#include <stdio.h> 
#include <pthread.h> 
#include <errno.h>
#include <stdlib.h> 
#include <time.h> 

/*
 * У вас в коде делается неявное предположение, что MATRIX_SIZE делится на STREAM_NUMBER.
 * В идеале его надо как-то обойти, либо явно это указать в комментарии. Лучше первое)
 */
#define STREAM_NUMBER 10
#define MATRIX_SIZE 1000

/*
 * Когда я выкачиваю код из репозитория, я получаю самую последнюю его версию.
 */

/*
 * Лучше, чтобы в названии ф-й были глаголы: Multiply, Print.
 */

void* Multiplication(void* arg); 
void Printing(int* data); 

int* A; 
int* B; 
int* C; 

int main() 
{ 
	int i = 0, j = 0;
	
	A = (int*)malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(int)); 
	B = (int*)malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(int)); 
	C = (int*)malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(int)); 

	srand(time(NULL)); 						//for correct work function rand()
	for(i = 0; i < MATRIX_SIZE; i++) 
	{ 
		for(j = 0; j < MATRIX_SIZE; j++) 
		{ 
			A[i * MATRIX_SIZE + j] = rand() % 100 - 50; 
			B[i * MATRIX_SIZE + j] = rand() % 100 - 50; 
		} 
	} 
	
	pthread_t threadIDs[STREAM_NUMBER];  
	unsigned int startTime = clock(); 
	for(i = 0; i < STREAM_NUMBER; i++) 
	{ 
		int proc = pthread_create(threadIDs + i, (pthread_attr_t*)NULL, Multiplication, (void*)(&i)); 
		if(proc) 
		{ 
			fprintf(stderr, "Process %d wasn't created, number of error %d\n", i, proc); 
			exit(-1); 
		} 
	} 

	for(i = 0; i < STREAM_NUMBER; i++) 
		pthread_join(threadIDs[i], (void**)NULL); 

	printf("Time: %f\n", (double)(clock() - startTime) / CLOCKS_PER_SEC); 
	
	//Printing(A);
	//printf("\n");
	//Printing(B);
	//printf("\n");
	//Printing(C);

	free(A); 
	free(B); 
	free(C); 

	return 0; 
} 

void Printing(int* data) 
{ 
	int i = 0, j = 0; 
	for(i = 0; i < MATRIX_SIZE; i++) 
	{ 
		for(j = 0; j < MATRIX_SIZE; j++) 
		{ 
			printf("%d\t", *(data + i * MATRIX_SIZE + j)); 
		} 
		printf("\n"); 
	} 
} 

void* Multiplication(void* arg) 
{ 
	int number = *((int*)arg); 
	int size = MATRIX_SIZE / STREAM_NUMBER; 

	int i = 0, j = 0, k = 0; 

	for(i = size * number; i < size * (number + 1); i++) 
		for(k = 0; k < MATRIX_SIZE; k++) 
			for(j = 0; j < MATRIX_SIZE; j++) 
				C[i * MATRIX_SIZE + k] = C[i * MATRIX_SIZE + k] + A[i * MATRIX_SIZE + j] * B[j * MATRIX_SIZE + k]; 
	return NULL; 
}
