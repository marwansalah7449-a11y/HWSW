/**
 * @file binarysearch.c
 * @brief Implementazione della ricerca binaria in C.
 * @author Marwan Salah
 * @date 29.09.2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_array_increasing(int arr[], int size) {
    arr[0] = rand() % 10; // Primo elemento casuale tra 0 e 9
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + (rand() % 10); // aggiungo un numero tra 0 e 9 al elemento precedente e assegno il risultato all'elemento attuale
    }
}

int binary_search(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int half = left + (right - left) / 2;

        if (arr[half] == target) {
            return half; // Elemento trovato, ritorna l'indice
        } else if (arr[half] < target) {
            left = half + 1; // Cerca nella metà destra
        } else {
            right = half - 1; // Cerca nella metà sinistra
        }
    }
    return -1; // Elemento non trovato
}

int main() {
    srand(time(NULL));
    int size;
    printf("Inserisci la dimensione dell'array: ");
    scanf("%d", &size);

    int arr[size];
    random_array_increasing(arr, size);
    printf("\nArray generato: | ");
    for (int i = 0; i < size; i++) {
        printf("%d | ", arr[i]);
    }
    printf("\n\n");

    int target;
    printf("inserisci il numero da cercare: ");
    scanf("%d", &target);

    int result = binary_search(arr, size, target);

    if (result != -1) { // se -1 = non trovato.
        printf("Elemento trovato alla posizione: %d\n", result);
    } else {
        printf("Elemento non trovato\n");
    }
}