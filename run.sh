#!/bin/bash
#SBATCH --time=10:00
#SBATCH --partition=cpar
#SBATCH --ntasks=16

module load papi/5.4.1
module load gcc/5.3.0
module load gcc/7.2.0

export OMP_PROC_BIND=true
export OMP_NUM_THREADS=16


N=100000000
W=10000000

make

./sort $N $W