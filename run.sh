#!/bin/bash

module load gcc/7.2.0
make 
make runpar CP_CLUSTER=4 THREADS=2 > cp4t2.txt
make runpar CP_CLUSTER=4 THREADS=4 > cp4t4.txt
make runpar CP_CLUSTER=4 THREADS=8 > cp4t8.txt
