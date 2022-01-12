#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

struct node {
  int size;
  int* list;
};

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int *array, int low, int high) {
  int pivot = array[high];
  int i = (low - 1), j;

  for (j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }
  swap(&array[i + 1], &array[high]);
  
  return (i + 1);
}

void quickSort(int *array, int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    
    quickSort(array, low, pi - 1);
    
    quickSort(array, pi + 1, high);
  }
}

void bucketSort(int *arr, int N, int M, int W) {
  int i, j, k, index;

  struct node * buckets = (struct node *) malloc(sizeof(struct node) * M);

  // Inicializar buckets vazios
  #pragma omp parallel for
  for(i=0; i<M; i++) {
    buckets[i].size = 0;
    buckets[i].list = NULL;
  }

  // Adicionar elementos aos buckets
  for(i=0; i<N; i++) {
    index = arr[i]/W;
    buckets[index].list = realloc(buckets[index].list, sizeof(int) * (buckets[index].size + 1));
    buckets[index].list[buckets[index].size++] = arr[i];
  }

  // Ordenar os buckets
  #pragma omp parallel for
  for(i=0; i<M; i++) {
    quickSort(buckets[i].list, 0, buckets[i].size-1);
  }

  // Voltar a por no array original
  for(i=0, j=0; i<M; i++) {
    for(k=0; k<buckets[i].size; k++) {
      arr[j++] = buckets[i].list[k];
    }
  }
}

void print(int* arr, int N) {
  int i;
  for (i = 0; i < N; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  if(argc != 3)
    return -1;

  // Ir buscar argumentos
  int N, M, W;
  sscanf(argv[1], "%d", &N);
  sscanf(argv[2], "%d", &W);
  M = N/W;

  // Gerar array aleatorio
  int i;
  int *arr = (int*) malloc(sizeof(int) * N);
  for(i=0; i<N; i++) {
    arr[i] = rand() % N;
  }

  // Correr bucketSort
  bucketSort(arr, N, M, W);
  
  return 0;
}
