CC = gcc

CFLAGS = -std=c99 -O2 -fopenmp -g -Wall

all: 
	$(CC) -o sequencial $(CFLAGS) src/sequencial_bucket_sort.c
	$(CC) -o parallel $(CFLAGS) src/parallel_bucket_sort.c

clean:
	rm -f parallel sequencial slurm* export