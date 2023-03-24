#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct {
	int * arr;
	int start;
	int end;
} argument;

void swap(int * a, int * b) {
	int aux = * a;
	* a = * b;
	* b = aux;
}

int partition(int * arr, int start, int end) {

	int p = arr[end];
	int ind = start - 1;

	for (int i = start; i <= end - 1; i++) {
		if (arr[i] < p) {
			ind++;
			swap(&arr[ind], &arr[i]);
		}
	}

	swap(&arr[ind + 1], &arr[end]);

	return ind + 1;
}

void *quick_sort(void * a) {


	argument * cpy = (argument *) a;

	int * arr = cpy -> arr;
	int start = cpy -> start;
	int end = cpy -> end;

	if (start < end) {
		int p = partition(arr, start, end);

		pthread_t t1, t2;

		argument a1 = {arr, start, p - 1};
		argument a2 = {arr, p + 1, end};

		pthread_create(&t1, NULL, quick_sort, &a1);
		pthread_create(&t2, NULL, quick_sort, &a2);

		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	}

	pthread_exit(NULL);
}

void printArray(int * arr, int size) {
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


int main()
{
	char * line = NULL;
	size_t len = 0;
	FILE * in = fopen("../input", "r");

	getline(&line, &len, in);

	int size = strtol(line, NULL, 10);
	int * arr = malloc(size * sizeof(int));
	int i = 0;

	while (i < size) {
		getline(&line, &len, in);
		arr[i] = strtol(line, NULL, 10);
		i++;
	}

	fclose(in);
	
	printf("unsorted array: \n");
	printArray(arr, size);


	argument a = {arr, 0, size - 1};
	
	pthread_t t;
	pthread_create(&t, NULL, quick_sort, &a);
	pthread_join(t, NULL);
	

	printf("Sorted array: \n");
	printArray(arr, size);

	free(arr);
	return 0;
}
