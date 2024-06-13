#include <stdio.h>
#include <stdlib.h>

// Функция для решения СЛАУ методом Гаусса
int sle(double **matrix, int n, int m, double *roots);

// Функции для ввода, вывода матрицы и вывода корней
void input(double **matrix, int *n, int *m);
void output(double **matrix, int n, int m);
void output_roots(double *roots, int n);

void main()
{
    double **matrix; // Матрица коэффициентов уравнений
    double *roots;   // Массив для корней уравнений
    int n, m;        // Размеры матрицы (n строк, m столбцов)
    int success;     // Переменная для проверки успешности решения СЛАУ

    input(matrix, &n, &m);  // Ввод матрицы
    roots = (double *)malloc(n * sizeof(double));  // Выделение памяти под массив корней

    if (roots == NULL) {
        printf("n/a\n");
        return;
    }

    success = sle(matrix, n, m, roots);  // Решение СЛАУ методом Гаусса

    if (success) {
        output_roots(roots, n);  // Вывод корней уравнений
    } else {
        printf("n/a\n");  // В случае ошибки выводим "n/a"
    }

    // Освобождение выделенной памяти
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(roots);
}

// Функция для решения СЛАУ методом Гаусса
int sle(double **matrix, int n, int m, double *roots) {
    // Пример реализации метода Гаусса можно найти в материалах или самостоятельно написать.
}

// Функция для ввода матрицы
void input(double **matrix, int *n, int *m) {
    // Реализация ввода матрицы из stdin
}

// Функция для вывода матрицы
void output(double **matrix, int n, int m) {
    // Реализация вывода матрицы
}

// Функция для вывода корней уравнений
void output_roots(double *roots, int n) {
    // Реализация вывода корней уравнений с заданной точностью
}















#include <stdio.h>
#include <stdlib.h>

// Функция для решения СЛАУ методом Гаусса
int sle(double **matrix, int n, int m, double *roots);

// Функции для ввода, вывода матрицы и вывода корней
void input(double **matrix, int *n, int *m);
void output(double **matrix, int n, int m);
void output_roots(double *roots, int n);

void main()
{
    double **matrix; // Матрица коэффициентов уравнений
    double *roots;   // Массив для корней уравнений
    int n, m;        // Размеры матрицы (n строк, m столбцов)
    int success;     // Переменная для проверки успешности решения СЛАУ

    input(matrix, &n, &m);  // Ввод матрицы

    roots = (double *)malloc(n * sizeof(double));  // Выделение памяти под массив корней

    if (roots == NULL) {
        printf("n/a\n");
        return;
    }

    success = sle(matrix, n, m, roots);  // Решение СЛАУ методом Гаусса

    if (success) {
        output_roots(roots, n);  // Вывод корней уравнений
    } else {
        printf("n/a\n");  // В случае ошибки выводим "n/a"
    }

    // Освобождение выделенной памяти
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(roots);
}

// Функция для ввода матрицы
void input(double **matrix, int *n, int *m) {
    FILE *file = fopen("sle.txt", "r");  // Открытие файла sle.txt для чтения

    if (file == NULL) {
        printf("n/a\n");
        exit(1);
    }

    fscanf(file, "%d %d", n, m);  // Считывание размеров матрицы

    // Выделение памяти под матрицу
    matrix = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        matrix[i] = (double *)malloc(*m * sizeof(double));
    }

    // Считывание элементов матрицы из файла
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }

    fclose(file);  // Закрытие файла
}

// Функция для вывода матрицы
void output(double **matrix, int n, int m) {
    // Реализация вывода матрицы
}

// Функция для вывода корней уравнений
void output_roots(double *roots, int n) {
    // Реализация вывода корней уравнений с заданной точностью
}
