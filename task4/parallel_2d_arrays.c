#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Функция для инициализации двумерного массива случайными числами
void init_2d_array(double** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = (double)(rand() % 1000) / 10.0;  // Случайные числа от 0 до 99.9
        }
    }
}

// Функция для проверки результатов
void verify_results(double** arr1, double** arr2, double** add, double** sub, 
                   double** mul, double** div, int rows, int cols) {
    int is_correct = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (add[i][j] != arr1[i][j] + arr2[i][j] ||
                sub[i][j] != arr1[i][j] - arr2[i][j] ||
                mul[i][j] != arr1[i][j] * arr2[i][j] ||
                (arr2[i][j] != 0 && div[i][j] != arr1[i][j] / arr2[i][j])) {
                is_correct = 0;
                break;
            }
        }
        if (!is_correct) break;
    }
    printf("Results are %s\n", is_correct ? "correct" : "incorrect");
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 4) {
        printf("Usage: %s <number_of_threads> [rows cols]\n", argv[0]);
        return 1;
    }

    int ROWS = 1000;    // Количество строк по умолчанию
    int COLS = 1000;    // Количество столбцов по умолчанию
    
    // Если переданы размеры массивов, используем их
    if (argc == 4) {
        ROWS = atoi(argv[2]);
        COLS = atoi(argv[3]);
        if (ROWS <= 0 || COLS <= 0) {
            printf("Error: Dimensions must be positive\n");
            return 1;
        }
    }
    
    const int N = ROWS * COLS; // Общее количество элементов
    
    // Выделение памяти для массивов
    double **arr1 = (double**)malloc(ROWS * sizeof(double*));
    double **arr2 = (double**)malloc(ROWS * sizeof(double*));
    double **add_result = (double**)malloc(ROWS * sizeof(double*));
    double **sub_result = (double**)malloc(ROWS * sizeof(double*));
    double **mul_result = (double**)malloc(ROWS * sizeof(double*));
    double **div_result = (double**)malloc(ROWS * sizeof(double*));
    
    for (int i = 0; i < ROWS; i++) {
        arr1[i] = (double*)malloc(COLS * sizeof(double));
        arr2[i] = (double*)malloc(COLS * sizeof(double));
        add_result[i] = (double*)malloc(COLS * sizeof(double));
        sub_result[i] = (double*)malloc(COLS * sizeof(double));
        mul_result[i] = (double*)malloc(COLS * sizeof(double));
        div_result[i] = (double*)malloc(COLS * sizeof(double));
    }
    
    // Инициализация массивов
    srand(time(NULL));
    init_2d_array(arr1, ROWS, COLS);
    init_2d_array(arr2, ROWS, COLS);
    
    // Получение количества потоков из аргумента командной строки
    int num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        printf("Error: Number of threads must be positive\n");
        // Освобождение памяти
        for (int i = 0; i < ROWS; i++) {
            free(arr1[i]);
            free(arr2[i]);
            free(add_result[i]);
            free(sub_result[i]);
            free(mul_result[i]);
            free(div_result[i]);
        }
        free(arr1);
        free(arr2);
        free(add_result);
        free(sub_result);
        free(mul_result);
        free(div_result);
        return 1;
    }
    omp_set_num_threads(num_threads);
    
    // Измерение времени начала
    double start_time = omp_get_wtime();

    // Параллельные операции
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            add_result[i][j] = arr1[i][j] + arr2[i][j];
            sub_result[i][j] = arr1[i][j] - arr2[i][j];
            mul_result[i][j] = arr1[i][j] * arr2[i][j];
            if (arr2[i][j] != 0) {
                div_result[i][j] = arr1[i][j] / arr2[i][j];
            } else {
                div_result[i][j] = 0;  // Защита от деления на ноль
            }
        }
    }

    // Измерение времени окончания
    double end_time = omp_get_wtime();
    double time_elapsed = end_time - start_time;

    printf("Parallel 2D Array Operations Results:\n");
    printf("Number of threads: %d\n", num_threads);
    printf("Array dimensions: %dx%d (total elements: %d)\n", ROWS, COLS, N);
    printf("Time elapsed: %f seconds\n", time_elapsed);
    
    // Проверка результатов
    verify_results(arr1, arr2, add_result, sub_result, mul_result, div_result, ROWS, COLS);

    // Освобождение памяти
    for (int i = 0; i < ROWS; i++) {
        free(arr1[i]);
        free(arr2[i]);
        free(add_result[i]);
        free(sub_result[i]);
        free(mul_result[i]);
        free(div_result[i]);
    }
    free(arr1);
    free(arr2);
    free(add_result);
    free(sub_result);
    free(mul_result);
    free(div_result);
    
    return 0;
} 