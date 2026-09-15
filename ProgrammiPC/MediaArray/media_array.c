/**
 * @file media_array.c
 * @brief Genera 50 valori casuali tra -10.0 e 10.0 e ne calcola la media.
 * @author Marwan Salah
 * @date 13.09.2026
 */
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 50

/**
 * @brief Riempie e stampa l'array, poi calcola e stampa la sua media.
 * Senza inizializzare un nuovo seme, rand ripete la sequenza a ogni avvio.
 *
 * @return 0 al termine del programma
 */
int main(void) {
    double valori[ARRAY_SIZE];
    double somma = 0.0;
    double media;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        valori[i] = -10.0 + 20.0 * ((double) rand() / RAND_MAX);
    }

    printf("Contenuto dell'array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%f\n", valori[i]);
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        somma += valori[i];
    }

    media = somma / ARRAY_SIZE;
    printf("Media: %f\n", media);

    return 0;
}
