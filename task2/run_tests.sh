#!/bin/bash

echo "Testing Quicksort Performance"
echo "============================"

# Array sizes to test
sizes=(100000 1000000 10000000)

# Number of threads to test
threads=(1 2 4 8)

for size in "${sizes[@]}"; do
    echo -e "\nArray size: $size"
    echo "------------------------"
    
    # Run sequential version
    echo "Sequential version:"
    ./sequential_quicksort $size
    
    # Run parallel version with different thread counts
    for thread in "${threads[@]}"; do
        echo -e "\nParallel version with $thread threads:"
        export OMP_NUM_THREADS=$thread
        ./parallel_quicksort $thread $size
    done
done 