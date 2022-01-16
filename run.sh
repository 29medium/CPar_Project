#!/bin/bash
#SBATCH --time=1:00
#SBATCH --partition=cpar
#SBATCH --ntasks=5

MY=/home/pg47556/CPar_Project
N=100000000
W=1000000

make

module load papi/5.4.1

time $MY/sort $N $W