#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>

void swap(int * a, int * b) {
	int aux = * a;
	* a = * b;
	* b = aux;
}

int partition(int * v, int start, int end) {

	int p = v[end];
	int ind = start - 1;

	for (int i = start; i <= end - 1; i++) {
		if (v[i] < p) {
			ind++;
			swap(&v[ind], &v[i]);
		}
	}

	swap(&v[ind + 1], &v[end]);

	return ind + 1;
}

void quick_sort(int * arr, int start, int end) {

	if (start < end) {
		int p = partition(arr, start, end);
		quick_sort(arr, start, p - 1);
		quick_sort(arr, p + 1, end);
	}
}

void printArray(int * arr, int size) {
	int i;
	for (i = 0; i < size; i++)
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

	quick_sort(arr, 0, size - 1);
	
	printf("Sorted array: \n");
	printArray(arr, size);

	free(arr);
	return 0;
}



	