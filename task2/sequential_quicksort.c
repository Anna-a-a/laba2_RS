#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Функция быстрой сортировки
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
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
    
    // Измерение времени начала
    clock_t start_time = clock();

    // Последовательная сортировка
    quicksort(arr, 0, N - 1);

    // Измерение времени окончания
    clock_t end_time = clock();
    double time_elapsed = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Проверка правильности сортировки
    int is_sorted = 1;
    for (int i = 1; i < N; i++) {
        if (arr[i] < arr[i-1]) {
            is_sorted = 0;
            break;
        }
    }

    printf("Sequential Quicksort Results:\n");
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