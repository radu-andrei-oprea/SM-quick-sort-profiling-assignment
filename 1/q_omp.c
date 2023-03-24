#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


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
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main(int argc, char *argv[]) {
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

  return 0;
}

