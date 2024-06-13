#include <stdio.h>
#include <stdlib.h>

// Функция для ввода матрицы
void input(int ***matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
        printf("n/a");
        exit(1);
    }

    *matrix = malloc(*n * sizeof(int *));
    if (*matrix == NULL) {
        printf("n/a");
        exit(1);
    }

    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = malloc(*m * sizeof(int));
        if ((*matrix)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*matrix)[j]);
            }
            free(*matrix);
            printf("n/a");
            exit(1);
        }
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &(*matrix)[i][j]) != 1) {
                for (int k = 0; k < *n; k++) {
                    free((*matrix)[k]);
                }
                free(*matrix);
                printf("n/a");
                exit(1);
            }
        }
    }
}

// Функция для вывода матрицы
void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }
}

// Функция для сравнения элементов (для qsort)
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Функция для сортировки матрицы змейкой по вертикали
void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int total_elements = n * m;
    int *temp = malloc(total_elements * sizeof(int));

    if (temp == NULL) {
        printf("n/a");
        exit(1);
    }

    for (int i = 0, k = 0; i < n; i++) {
        for (int j = 0; j < m; j++, k++) {
            temp[k] = matrix[i][j];
        }
    }

    qsort(temp, total_elements, sizeof(int), compare);

    for (int i = 0, k = 0; i < n; i++) {
        for (int j = 0; j < m; j++, k++) {
            result_matrix[i][j] = temp[k];
        }
    }

    free(temp);
}

// Функция для сортировки матрицы змейкой по горизонтали
void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int total_elements = n * m;
    int *temp = malloc(total_elements * sizeof(int));

    if (temp == NULL) {
        printf("n/a");
        exit(1);
    }

    for (int i = 0, k = 0; i < n; i++) {
        for (int j = 0; j < m; j++, k++) {
            temp[k] = matrix[i][j];
        }
    }

    qsort(temp, total_elements, sizeof(int), compare);

    for (int i = 0, k = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++, k++) {
                result_matrix[i][j] = temp[k];
            }
        } else {
            for (int j = m - 1; j >= 0; j--, k++) {
                result_matrix[i][j] = temp[k];
            }
        }
    }

    free(temp);
}

int main() {
    int **matrix = NULL, **result = NULL;
    int n, m;

    // Ввод матрицы
    input(&matrix, &n, &m);

    // Выделение памяти для результирующей матрицы
    result = malloc(n * sizeof(int *));
    if (result == NULL) {
        free_matrix(matrix, n);
        printf("n/a");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        result[i] = malloc(m * sizeof(int));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free_matrix(matrix, n);
            printf("n/a");
            exit(1);
        }
    }

    // Сортировка и вывод матрицы змейкой по вертикали
    sort_vertical(matrix, n, m, result);
    output(result, n, m);
    printf("\n");

    // Сортировка и вывод матрицы змейкой по горизонтали
    sort_horizontal(matrix, n, m, result);
    output(result, n, m);

    // Освобождение памяти
    free_matrix(result, n);
    free_matrix(matrix, n);

    return 0;
}

// Функция для освобождения памяти матрицы
void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
