#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для инициализации массива случайными числами
void init_array(double* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (double)(rand() % 1000) / 10.0;  // Случайные значения от 0 до 99.9
    }
}

// Функция для проверки правильности результатов
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
    printf("Результаты %s\n", is_correct ? "корректны" : "некорректны");
}

int main() {
    const int N = 1000000;  // Размер массивов
    double *arr1 = (double*)malloc(N * sizeof(double));
    double *arr2 = (double*)malloc(N * sizeof(double));
    double *add_result = (double*)malloc(N * sizeof(double));
    double *sub_result = (double*)malloc(N * sizeof(double));
    double *mul_result = (double*)malloc(N * sizeof(double));
    double *div_result = (double*)malloc(N * sizeof(double));
    
    // Инициализация массивов случайными числами
    srand(time(NULL));
    init_array(arr1, N);
    init_array(arr2, N);
    
    // Измерение времени начала
    clock_t start_time = clock();

    // Последовательные арифметические операции
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

    printf("Результаты последовательных операций над массивами:\n");
    printf("Размер массива: %d\n", N);
    printf("Время выполнения: %f секунд\n", time_elapsed);
    
    // Проверка результатов
    verify_results(arr1, arr2, add_result, sub_result, mul_result, div_result, N);

    // Освобождение памяти
    free(arr1);
    free(arr2);
    free(add_result);
    free(sub_result);
    free(mul_result);
    free(div_result);
    
    return 0;
} 