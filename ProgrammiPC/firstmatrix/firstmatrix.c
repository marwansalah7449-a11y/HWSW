/**
 * @file firstmatrix.c
 * @brief stampa una scacchiera quadrata di dimensione scelta dall'utente
 * @author Marwan Salah
 * @date 21.10.2026
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Stampa la matrice
 * @param matrix Puntatore alla matrice
 * @param rows Numero di righe della matrice
 * @param cols Numero di colonne della matrice
 */
void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
/**
 * @brief Libera la memoria allocata per la matrice
 * @param matrix Puntatore alla matrice
 * @param rows Numero di righe della matrice
 */
void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int rows;
    int cols;

    // Chiede all'utente il numero di righe e colonne
    printf("Inserisci il numero di colonne della scacchiera: ");
    scanf("%d", &cols);
    printf("Inserisci il numero di righe della scacchiera: ");
    scanf("%d", &rows);

    // Alloca dinamicamente la memoria per la matrice
    int **m = (int **)malloc(rows * sizeof(int *));
    for (size_t i = 0; i < rows; i++) {
        m[i] = (int *)malloc(cols * sizeof(int));
    }

    // Riempie la matrice con valori alternati (0 e 1) per creare l'effetto scacchiera
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m [i][j] = !((i + j) % 2); 
        }
    }

    // Stampa la matrice
    printMatrix(m, rows, cols);

    // Libera la memoria allocata per la matrice
    freeMatrix(m, rows);

    return 0;
}