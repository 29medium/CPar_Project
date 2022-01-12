#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

struct node {
  int size;
  int* list;
};

int compare (const void * a, const void * b) {
 return ( *(int*)a - *(int*)b );
}

int largest(int arr[], int n)
{
  int i, max = arr[0];

  for (i = 1; i < n; i++)      
    if (arr[i] > max)
      max = arr[i];

  return max;
}

void bucketSort(int arr[], int N, int M) {
  int i, j, k, index;
  int size = largest(arr, N) / N;
  struct node * buckets = (struct node *) malloc(sizeof(struct node) * M);

  // Inicializar buckets vazios
  for(i=0; i<M; i++) {
    buckets[i].size = 0;
    buckets[i].list = NULL;
  }

  // Adicionar elementos aos buckets
  for(i=0; i<N; i++) {
    index = arr[i]/size - 1;
    buckets[index].list = realloc(buckets[index].list, sizeof(int) * (buckets[index].size + 1));
    buckets[index].list[buckets[index].size++] = arr[i];
  }

  // Ordenar os buckets
  for(i=0; i<M; i++) {
    qsort(buckets[i].list, buckets[i].size, sizeof(int), compare);
  }

  // Voltar a por no array original
  for(i=0, j=0; i<M; i++) {
    for(k=0; k<buckets[i].size; k++) {
      arr[j++] = buckets[i].list[k];
    }
  }
}

void print(int ar[], int N) {
  int i;
  for (i = 0; i < N; ++i) {
    printf("%d ", ar[i]);
  }
  printf("\n");
}

int main(void) {
  int N = 7;
  int M = 7;
  int array[7] = {42, 32, 33, 52, 37, 47, 51};

  print(array, N);

  float t1 =  omp_get_wtime();

  bucketSort(array, N, M);
  
  float t2 =  omp_get_wtime();

  print(array, N);

  printf("Time: %f\n", t2-t1)

  return 0;
}