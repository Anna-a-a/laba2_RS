#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для инициализации массива случайными числами
void init_array(double* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (double)(rand() % 1000) / 10.0;  // Случайные числа от 0 до 99.9
    }
}

// Функция для проверки результатов
void verify_results(double* arr1, double* arr2, double* add, double* sub, double* mul, double* div, int size) {
    int is_correct = 1;
    for (int i = 0; i < size; i++) {
        if (add[i] != arr1[i] + arr2[i] ||
            sub[i] != arr1[i] - arr2[i] ||
            mul[i] != arr1[i] * arr2[i] ||
            (arr2[i] != 0 && div[i] != arr1[i] / arr2[i])) {
            is_correct = 0;
            break;
        }
    }
    printf("Results are %s\n", is_correct ? "correct" : "incorrect");
}

int main() {
    const int N = 1000000;  // Размер массивов
    double *arr1 = (double*)malloc(N * sizeof(double));
    double *arr2 = (double*)malloc(N * sizeof(double));
    double *add_result = (double*)malloc(N * sizeof(double));
    double *sub_result = (double*)malloc(N * sizeof(double));
    double *mul_result = (double*)malloc(N * sizeof(double));
    double *div_result = (double*)malloc(N * sizeof(double));
    
    // Инициализация массивов
    srand(time(NULL));
    init_array(arr1, N);
    init_array(arr2, N);
    
    // Измерение времени начала
    clock_t start_time = clock();

    // Последовательные операции
    for (int i = 0; i < N; i++) {
        add_result[i] = arr1[i] + arr2[i];
        sub_result[i] = arr1[i] - arr2[i];
        mul_result[i] = arr1[i] * arr2[i];
        if (arr2[i] != 0) {
            div_result[i] = arr1[i] / arr2[i];
        } else {
            div_result[i] = 0;  // Защита от деления на ноль
        }
    }

    // Измерение времени окончания
    clock_t end_time = clock();
    double time_elapsed = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Sequential Array Operations Results:\n");
    printf("Array size: %d\n", N);
    printf("Time elapsed: %f seconds\n", time_elapsed);
    
    // Проверка результатов
    verify_results(arr1, arr2, add_result, sub_result, mul_result, div_result, N);
    
    // Вывод нескольких элементов для проверки
    printf("\nFirst 5 elements of results:\n");
    printf("Index\tArray1\tArray2\tAdd\tSub\tMul\tDiv\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
               i, arr1[i], arr2[i], add_result[i], sub_result[i], mul_result[i], div_result[i]);
    }

    // Освобождение памяти
    free(arr1);
    free(arr2);
    free(add_result);
    free(sub_result);
    free(mul_result);
    free(div_result);
    
    return 0;
} 