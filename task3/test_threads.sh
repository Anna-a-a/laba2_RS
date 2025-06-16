#!/bin/bash

echo "Testing Arrays Performance with Different Thread Counts"
echo "===================================================="

# Number of threads to test
threads=(1 2 4 8 16)

# Run sequential version
echo -e "\nSequential version:"
./sequential_arrays 1000000

# Run parallel version with different thread counts
for thread in "${threads[@]}"; do
    echo -e "\nParallel version with $thread threads:"
    export OMP_NUM_THREADS=$thread
    ./parallel_arrays $thread
done 