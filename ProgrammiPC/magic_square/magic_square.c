/**
 * @file magic_square.c
 * @brief verifica se una matrice è un quadrato magico.
 * @author Marwan Salah
 * @date 27.10.2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_magic(int **m , int size) {
    if (size <= 0) {
        return false;
    }

    long long max_value = (long long)size * size;
    long long magic_constant = (long long)size * (max_value + 1) / 2;
    for (long long i = 0; i < max_value; i++) {
        int value = m[i / size][i % size];
        if (value < 1 || value > max_value) {
            return false;
        }
        for (long long previous = 0; previous < i; previous++) {
            if (value == m[previous / size][previous % size]) {
                return false;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        long long row_sum = 0;
        for (int j = 0; j < size; j++) {
            row_sum += m[i][j];
        }
        if (row_sum != magic_constant) {
            return false;
        }
    }

    for (int j = 0; j < size; j++) {
        long long col_sum = 0;
        for (int i = 0; i < size; i++) {
            col_sum += m[i][j];
        }
        if (col_sum != magic_constant) {
            return false;
        }
    }

    long long diag1_sum = 0;
    for (int i = 0; i < size; i++) {
        diag1_sum += m[i][i];
    }
    if (diag1_sum != magic_constant) {
        return false;
    }

    long long diag2_sum = 0;
    for (int i = 0; i < size; i++) {
        diag2_sum += m[i][size - 1 - i];
    }
    if (diag2_sum != magic_constant) {
        return false;
    }

    return true;
}


int main() {
    int size;
    printf("Inserisci la dimensione della matrice: ");
    scanf("%d", &size);

    int **m = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        m[i] = (int *)malloc(size * sizeof(int));
    }

    printf("Inserisci gli elementi della matrice:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &m[i][j]);
        }
    }
    printf("La matrice inserita è:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    if (is_magic(m, size)) {
        printf("Is magic\n");
    } else {
        printf("Is not magic\n");
    }

    // Liberazione della memoria
    for (int i = 0; i < size; i++) {
        free(m[i]);
    }
    free(m);

    return 0;
}