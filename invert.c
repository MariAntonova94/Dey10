#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для ввода матрицы
void input(double ***matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0 || *n != *m) {
        printf("n/a");
        exit(1); // Проверка корректности ввода и условий на квадратную матрицу
    }

    *matrix = (double **)malloc(*n * sizeof(double *));
    if (*matrix == NULL) {
        printf("n/a");
        exit(1); // Проверка успешного выделения памяти
    }

    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = (double *)malloc(*m * sizeof(double));
        if ((*matrix)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*matrix)[j]);
            }
            free(*matrix);
            printf("n/a");
            exit(1); // Проверка успешного выделения памяти для каждой строки
        }
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%lf", &(*matrix)[i][j]) != 1) {
                for (int k = 0; k < *n; k++) {
                    free((*matrix)[k]);
                }
                free(*matrix);
                printf("n/a");
                exit(1); // Проверка корректности ввода элементов матрицы
            }
        }
    }
}

// Функция для освобождения памяти матрицы
void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]); // Освобождение памяти для каждой строки
    }
    free(matrix); // Освобождение памяти для массива указателей
}

// Функция для вывода матрицы с заданной точностью
void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.6lf", matrix[i][j]); // Вывод элемента с заданной точностью
            if (j < m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// Функция для вычисления обратной матрицы
void invert(double **matrix, int n, int m) {
    double **augmented_matrix = (double **)malloc(n * sizeof(double *));
    if (augmented_matrix == NULL) {
        printf("n/a");
        exit(1); // Проверка успешного выделения памяти для расширенной матрицы
    }

    for (int i = 0; i < n; i++) {
        augmented_matrix[i] = (double *)malloc(2 * n * sizeof(double));
        if (augmented_matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(augmented_matrix[j]);
            }
            free(augmented_matrix);
            printf("n/a");
            exit(1); // Проверка успешного выделения памяти для каждой строки расширенной матрицы
        }

        for (int j = 0; j < n; j++) {
            augmented_matrix[i][j] = matrix[i][j]; // Копирование исходной матрицы в расширенную
            augmented_matrix[i][j + n] = (i == j) ? 1.0 : 0.0; // Инициализация единичной матрицы
        }
    }

    for (int i = 0; i < n; i++) {
        if (fabs(augmented_matrix[i][i]) < 1e-6) {
            int swap_row = -1;
            for (int j = i + 1; j < n; j++) {
                if (fabs(augmented_matrix[j][i]) > 1e-6) {
                    swap_row = j;
                    break;
                }
            }
            if (swap_row == -1) {
                free_matrix(augmented_matrix, n);
                printf("n/a");
                exit(1); // Проверка на нулевой элемент на главной диагонали и попытка обмена строками
            }
            double *temp_row = augmented_matrix[i];
            augmented_matrix[i] = augmented_matrix[swap_row];
            augmented_matrix[swap_row] = temp_row;
        }

        double pivot = augmented_matrix[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmented_matrix[i][j] /= pivot; // Деление строки на ведущий элемент
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double ratio = augmented_matrix[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented_matrix[k][j] -= ratio * augmented_matrix[i][j]; // Вычитание строки с коэффициентом
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = augmented_matrix[i][j + n]; // Копирование обратной матрицы из расширенной
        }
    }

    free_matrix(augmented_matrix, n); // Освобождение памяти расширенной матрицы
}

int main() {
    double **matrix = NULL;
    int n, m;

    // Ввод матрицы
    input(&matrix, &n, &m);

    // Проверка на квадратность матрицы
    if (n != m) {
        printf("n/a");
        free_matrix(matrix, n);
        return 1;
    }

    // Вычисление обратной матрицы
    invert(matrix, n, m);

    // Вывод результата
    output(matrix, n, m);

    // Освобождение памяти
    free_matrix(matrix, n);

    return 0;
}
