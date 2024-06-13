

// Quest 1

#include <stdio.h>
#include <stdlib.h>

// Функция для ввода матрицы
void input_matrix(int ***matrix, int *rows, int *cols);
// Функция для вывода матрицы
void output_matrix(int **matrix, int rows, int cols);
// Функция для сортировки матрицы "змейкой"
void sort_matrix_snake(int **matrix, int rows, int cols);
// Функция для освобождения памяти матрицы
void free_matrix(int **matrix, int rows);
// Функция для сравнения элементов (для qsort)
int compare(const void *a, const void *b);

int main() {
    int **matrix = NULL; // Указатель на матрицу
    int rows = 0, cols = 0; // Переменные для хранения размеров матрицы

    // Ввод матрицы
    input_matrix(&matrix, &rows, &cols);

    // Проверка на корректность ввода
    if (rows <= 0 || cols <= 0 || matrix == NULL) {
        printf("n/a");
        return 1; // Завершение программы с кодом ошибки
    }

    // Сортировка и вывод матрицы змейкой по вертикали
    sort_matrix_snake(matrix, rows, cols);
    output_matrix(matrix, rows, cols);
    printf("\n"); // Печать пустой строки между выводами матриц

    // Сортировка и вывод матрицы змейкой по горизонтали
    sort_matrix_snake(matrix, rows, cols);
    output_matrix(matrix, rows, cols);

    // Освобождение памяти
    free_matrix(matrix, rows);
    return 0; // Успешное завершение программы
}

// Функция для ввода матрицы
void input_matrix(int ***matrix, int *rows, int *cols) {
    // Ввод количества строк и столбцов матрицы
    if (scanf("%d %d", rows, cols) != 2 || *rows <= 0 || *cols <= 0) {
        *matrix = NULL;
        return;
    }

    // Выделение памяти для строк матрицы
    *matrix = malloc(*rows * sizeof(int *));
    if (*matrix == NULL) {
        *matrix = NULL;
        return;
    }

    // Выделение памяти для каждого столбца матрицы
    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = malloc(*cols * sizeof(int));
        if ((*matrix)[i] == NULL) {
            // Освобождение ранее выделенной памяти в случае ошибки
            for (int j = 0; j < i; j++) {
                free((*matrix)[j]);
            }
            free(*matrix);
            *matrix = NULL;
            return;
        }
    }

    // Ввод элементов матрицы
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            if (scanf("%d", &(*matrix)[i][j]) != 1) {
                // Освобождение памяти и указание на ошибку в случае некорректного ввода
                free_matrix(*matrix, *rows);
                *matrix = NULL;
                return;
            }
        }
    }
}

// Функция для вывода матрицы
void output_matrix(int **matrix, int rows, int cols) {
    // Печать элементов матрицы
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) {
                printf(" "); // Печать пробела между элементами
            }
        }
        if (i < rows - 1) {
            printf("\n"); // Печать новой строки между строками матрицы
        }
    }
}

// Функция для сортировки матрицы "змейкой"
void sort_matrix_snake(int **matrix, int rows, int cols) {
    int total_elements = rows * cols; // Общее количество элементов в матрице
    int *temp = malloc(total_elements * sizeof(int)); // Временный массив для сортировки

    if (temp == NULL) {
        printf("n/a");
        return;
    }

    // Копирование элементов матрицы во временный массив
    for (int i = 0, k = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++, k++) {
            temp[k] = matrix[i][j];
        }
    }

    // Сортировка временного массива
    qsort(temp, total_elements, sizeof(int), compare);

    // Заполнение матрицы отсортированными элементами "змейкой"
    for (int i = 0, k = 0; i < rows; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < cols; j++, k++) {
                matrix[i][j] = temp[k];
            }
        } else {
            for (int j = cols - 1; j >= 0; j--, k++) {
                matrix[i][j] = temp[k];
            }
        }
    }

    free(temp); // Освобождение временного массива
}

// Функция для освобождения памяти матрицы
void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]); // Освобождение памяти для каждого столбца
    }
    free(matrix); // Освобождение памяти для строк
}

// Функция для сравнения элементов (для qsort)
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b); // Сравнение двух целых чисел
}
