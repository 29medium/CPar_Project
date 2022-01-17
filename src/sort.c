#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

struct node
{
	int size;
	int *list;
};

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int *array, int low, int high)
{
	int pivot = array[high];
	int i = (low - 1), j;

	for (j = low; j < high; j++)
	{
		if (array[j] <= pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[high]);

	return (i + 1);
}

void quickSort(int *array, int low, int high)
{
	if (low < high)
	{
		int pi = partition(array, low, high);

		quickSort(array, low, pi - 1);
		quickSort(array, pi + 1, high);
	}
}

void bucketSort(int *arr, int N, int M, int W)
{
	int i, k, j, size, index;

	struct node *buckets = (struct node *)malloc(sizeof(struct node) * M);

	// Inicializar buckets vazios
#pragma omp parallel for schedule(static)
	for (i = 0; i < M; i++)
	{
		buckets[i].size = 0;
		buckets[i].list = NULL;
	}

	// Adicionar elementos aos buckets
	for (i = 0; i < N; i++)
	{
		index = arr[i] / W;
		buckets[index].list = realloc(buckets[index].list, sizeof(int) * (buckets[index].size + 1));
		buckets[index].list[buckets[index].size++] = arr[i];
	}

	// Ordenar os buckets
#pragma omp parallel for schedule(dynamic)
	for (i = 0; i < M; i++)
	{
		quickSort(buckets[i].list, 0, buckets[i].size - 1);

	}

	// Voltar a por no array original
#pragma omp parallel for schedule(static) private(size)
	for (i = 0; i < M; i++)
	{
		size = 0;
		for(j = 0; j < i; j++)
			size += buckets[j].size;

		for (k = 0; k < buckets[i].size; k++)
		{
			arr[size+k] = buckets[i].list[k];
		}
		
	}
	// for (i = 0, j = 0; i < M; i++)
    // {
    //     for (k = 0; k < buckets[i].size; k++)
    //     {
    //         arr[j++] = buckets[i].list[k];
    //     }
    // }
}

void print(int *arr, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	double start, end;
	if (argc != 3)
		return -1;

	// Ir buscar argumentos
	int N, M, W;
	sscanf(argv[1], "%d", &N);
	sscanf(argv[2], "%d", &W);
	M = N / W;

	// Gerar array aleatorio
	int i;
	int *arr = (int *)malloc(sizeof(int) * N);

	for (i = 0; i < N; i++)
	{
		arr[i] = rand() % N;
	}

	start = omp_get_wtime();
	// Correr bucketSort
	bucketSort(arr, N, M, W);
	end = omp_get_wtime();

	printf("N: %d, M: %d, W: %d\n", N,M,W);
	printf("Time: %f\n", end-start);

	print(arr, N);

	return 0;
}
