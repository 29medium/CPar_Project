#!/bin/bash
#SBATCH --partition=cpar
#SBATCH --ntasks=64

module load papi/5.4.1
module load gcc/5.3.0
module load gcc/7.2.0

export OMP_PROC_BIND=true
export OMP_NUM_THREADS=64

make

./sort 10000000 1000000
./sort 10000000 100000
./sort 10000000 10000

./sort 100000000 10000000
./sort 100000000 1000000
./sort 100000000 100000

./sort 1000000000 100000000
./sort 1000000000 10000000
./sort 1000000000 1000000
