/**
 * @file checker.c
 * @brief Chiede un codice prodotto e verifica che sia valido controllandone lunghezza, caratteri e CRC.
 * @author Marwan Salah
 * @date 28.09.2026
 */
#include <stdio.h>
#include <string.h>

#define MIN_SIZE 2
#define MAX_SIZE 200

/**
 * @brief Controlla che il codice sia lungo da MIN_SIZE a MAX_SIZE caratteri, CRC compreso.
 *
 * @param code puntatore alla stringa del codice
 * @return 1 se il codice ha una lunghezza valida, 0 altrimenti
 */
int check_size(char *code) {
    size_t lunghezza = strlen(code);

    return lunghezza >= MIN_SIZE && lunghezza <= MAX_SIZE;
}

/**
 * @brief Controlla che ogni carattere del codice sia una cifra da '0' a '9'.
 *
 * @param code puntatore alla stringa del codice
 * @return 1 se il codice contiene solo cifre, 0 altrimenti
 */
int check_chars(char *code) {
    while (*code) {
        if (*code < '0' || *code > '9') {
            return 0;
        }
        code++;
    }

    return 1;
}

/**
 * @brief Calcola il CRC sommando i valori delle cifre del codice, escluso l'ultimo carattere, modulo 10.
 *
 * @param code puntatore alla stringa del codice
 * @return il CRC calcolato, da 0 a 9
 */
int get_crc(char *code) {
    int somma = 0;

    while (*code && *(code + 1)) {
        somma += *code - '0';
        code++;
    }

    return somma % 10;
}

int main(void) {
    char code[MAX_SIZE + 2];

    printf("Digita un codice: ");
    if (fgets(code, sizeof(code), stdin) == NULL) {
        code[0] = '\0';
    }
    code[strcspn(code, "\r\n")] = '\0';

    if (check_size(code) && check_chars(code) && get_crc(code) == code[strlen(code) - 1] - '0') {
        printf("Codice valido\n");
    } else {
        printf("Codice non valido\n");
    }

    return 0;
}
