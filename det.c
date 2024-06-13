#include <stdio.h> // Подключение библиотеки для работы с вводом-выводом
#include <stdlib.h> // Подключение библиотеки для работы с динамической памятью
#include <math.h> // Подключение библиотеки для математических функций

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

// Функция для вычисления определителя матрицы
double det(double **matrix, int n) {
    double determinant = 1;
    double **temp_matrix = (double **)malloc(n * sizeof(double *));
    if (temp_matrix == NULL) {
        return NAN; // Проверка успешного выделения памяти для временной матрицы
    }

    for (int i = 0; i < n; i++) {
        temp_matrix[i] = (double *)malloc(n * sizeof(double));
        if (temp_matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(temp_matrix[j]);
            }
            free(temp_matrix);
            return NAN; // Проверка успешного выделения памяти для каждой строки временной матрицы
        }
        for (int j = 0; j < n; j++) {
            temp_matrix[i][j] = matrix[i][j]; // Копирование исходной матрицы во временную
        }
    }

    for (int i = 0; i < n; i++) {
        if (fabs(temp_matrix[i][i]) < 1e-6) {
            int swap_row = -1;
            for (int j = i + 1; j < n; j++) {
                if (fabs(temp_matrix[j][i]) > 1e-6) {
                    swap_row = j;
                    break;
                }
            }
            if (swap_row == -1) {
                free_matrix(temp_matrix, n);
                return 0.0; // Проверка на нулевой элемент на главной диагонали и попытка обмена строками
            }
            double *temp_row = temp_matrix[i];
            temp_matrix[i] = temp_matrix[swap_row];
            temp_matrix[swap_row] = temp_row;
            determinant = -determinant; // Изменение знака определителя при обмене строк
        }
        determinant *= temp_matrix[i][i];
        for (int j = i + 1; j < n; j++) {
            double ratio = temp_matrix[j][i] / temp_matrix[i][i];
            for (int k = i; k < n; k++) {
                temp_matrix[j][k] -= ratio * temp_matrix[i][k];
            }
        }
    }

    free_matrix(temp_matrix, n); // Освобождение памяти временной матрицы
    return determinant;
}

// Функция для вывода определителя
void output(double determinant) {
    if (isnan(determinant)) {
        printf("n/a");
    } else {
        printf("%.6lf", determinant); // Вывод определителя с точностью 6 знаков после запятой
    }
}

int main() {
    double **matrix = NULL;
    int n, m;

    // Ввод матрицы
    input(&matrix, &n, &m);

    // Вычисление определителя
    double determinant = det(matrix, n);

    // Вывод результата
    output(determinant);

    // Освобождение памяти
    free_matrix(matrix, n);

    return 0;
}
