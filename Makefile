all: 
	gcc -O2 -g -o sequencial src/sequencial_bucket_sort.c
	gcc -O2 -g -o parallel src/parallel_bucket_sort.c