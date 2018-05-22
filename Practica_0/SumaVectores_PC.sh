#!/bin/bash

export OMP_THREAD_LIMIT=12
echo "Nº de threads inicial: $OMP_THREAD_LIMIT"

for ((N=65536;N<67108865;N=N*2));
do
  ./SumaVectoresC $N
done
