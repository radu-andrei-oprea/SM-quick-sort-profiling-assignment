#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

void quick_sort(int * arr, int start, int end) {

	if (start < end) {
	    int p = partition(arr, start, end);
	    
	    #pragma omp parallel sections
	    {
	      #pragma omp section
	      {
	        quick_sort(arr, start, p - 1);
	      }

	      #pragma omp section
	      {
	        quick_sort(arr, p + 1, end);
	      }
	    }
  	}
}

void printArray(int * arr, int size) {
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


int main(int argc, char **argv) {
 
	MPI_Init(&argc, &argv);

	int procs;
	int rank;
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int size;
	int * arr;

	if (rank == 0) {

		scanf("%d", &size);

		arr = malloc(size * sizeof(int));
		int i = 0;

		while (i < size) {
			scanf("%d", &arr[i]);
			i++;
		}

		printf("unsorted array: \n");
		printArray(arr, size);

	}

	MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

	
	int split_size = size / procs;
	int remainder = size % procs;


	int *split_arr = malloc(split_size * sizeof(int));


	MPI_Scatter(arr, split_size, MPI_INT, split_arr, split_size, MPI_INT, 0, MPI_COMM_WORLD);

	quick_sort(split_arr, 0, split_size - 1);

	MPI_Gather(split_arr, split_size, MPI_INT, arr, split_size, MPI_INT, 0, MPI_COMM_WORLD);


	if (rank == 0 && remainder > 0) {
		quick_sort(arr + size - remainder, 0, remainder - 1);
	}

	if (rank == 0) {
		printf("Sorted array: \n");
		printArray(arr, size);
		free(arr);
	}

	free(split_arr);

	MPI_Finalize();
	return 0;
}
