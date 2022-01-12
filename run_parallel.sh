#!/bin/bash

MY=/home/pg47556/CPar_Project
N=10000000
W=100
T=2

export OMP_NUM_THREADS=$T

time $MY/parallel $N $W
time $MY/parallel $N $W
time $MY/parallel $N $W