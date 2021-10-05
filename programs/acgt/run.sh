#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "usage: run inner_iterations outer_iterations"
  exit 1
fi

iterations=$1
n=$2
cout="out_c.txt"
pyout="out_py.txt"

echo 'C:'
#time for ((i = 0; i < $n; i++))
i=0
time while [ $i -lt $n ]
  do
    ./acgt $iterations
    i=$((i + 1))
  done > $cout && wc $cout | awk '{print $1/3}'
echo ''
echo 'Python:'
i=0
time while [ $i -lt $n ]
  do
    python3 acgt.py $iterations
    i=$((i + 1))
  done > $pyout && wc $pyout | awk '{print $1/3}'
