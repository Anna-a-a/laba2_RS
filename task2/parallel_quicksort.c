#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Функция для обмена элементов
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Функция разделения массива
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Параллельная быстрая сортировка
void parallel_quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        #pragma omp task
        {
            parallel_quicksort(arr, low, pi - 1);
        }
        
        #pragma omp task
        {
            parallel_quicksort(arr, pi + 1, high);
        }
    }
}

int main() {
    const int N = 1000000;  // Размер массива
    int* arr = (int*)malloc(N * sizeof(int));
    
    // Инициализация массива случайными числами
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 1000000;  // Случайные числа от 0 до 999999
    }
    
    // Получение количества потоков
    int num_threads = omp_get_max_threads();
    if (getenv("OMP_NUM_THREADS")) {
        num_threads = atoi(getenv("OMP_NUM_THREADS"));
    }
    omp_set_num_threads(num_threads);
    
    // Измерение времени начала
    double start_time = omp_get_wtime();

    // Параллельная сортировка
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallel_quicksort(arr, 0, N - 1);
        }
    }

    // Измерение времени окончания
    double end_time = omp_get_wtime();
    double time_elapsed = end_time - start_time;

    // Проверка правильности сортировки
    int is_sorted = 1;
    for (int i = 1; i < N; i++) {
        if (arr[i] < arr[i-1]) {
            is_sorted = 0;
            break;
        }
    }

    printf("Parallel Quicksort Results:\n");
    printf("Number of threads: %d\n", num_threads);
    printf("Array size: %d\n", N);
    printf("Time elapsed: %f seconds\n", time_elapsed);
    printf("Array is %s\n", is_sorted ? "correctly sorted" : "not sorted correctly");
    
    // Вывод нескольких элементов для проверки
    printf("First 5 elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nLast 5 elements: ");
    for (int i = N-5; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
} 