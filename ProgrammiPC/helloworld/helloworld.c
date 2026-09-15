/**
 * @file helloworld.c
 * @brief Stampa "Hello, World!" per i numeri primi da 1 a 999.
 * Il controllo originale include anche il numero 1.
 * @author Marwan Salah
 * @date 05.09.2026
 */
#include <stdio.h>

/**
 * @brief Prova tutti i divisori da 2 a numero - 1, senza fermare il ciclo.
 * Il metodo originale restituisce 1 anche per i numeri minori di 2.
 *
 * @param numero il numero da controllare
 * @return 1 se il ciclo non trova divisori, 0 altrimenti
 */
int is_prime(int numero) {
    int primo = 1;

    for (int j = 2; j < numero; j++) {
        if (numero % j == 0) {
            primo = 0;
        }
    }

    return primo;
}

/**
 * @brief Stampa un saluto per ogni numero da 1 a 999 accettato da is_prime.
 *
 * @return 0 al termine del programma
 */
int main(void) {
    for (int i = 1; i < 1000; i++) {
        if (is_prime(i)) {
            printf("%03d Hello, World!\n", i);
        }
    }

    return 0;
}
