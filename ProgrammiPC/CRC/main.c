/**
 * @file checker.c
 * @brief Chiede un codice e verifica che sia valido controllando lunghezza, caratteri e CRC.
 * @author Marwan Salah
 * @date 28.09.2026
 */
#include <stdio.h>

#define MIN_SIZE 2
#define MAX_SIZE 200

/**
 * @brief Controlla che il codice sia lungo da MIN_SIZE a MAX_SIZE caratteri.
 *
 * @param code puntatore alla stringa del codice
 * @return 1 se il codice ha una lunghezza valida, altrimenti 0 
 */
int check_size(char *code) {
    int lunghezza = 0;

    while (*code != '\0') {
        lunghezza++;
        code++;
    }

    return lunghezza >= MIN_SIZE && lunghezza <= MAX_SIZE;
}

/**
 * @brief Controlla che ogni carattere del codice sia una cifra da '0' a '9'.
 *
 * @param code puntatore alla stringa del codice
 * @return 1 se il codice contiene solo cifre, altrimenti 0 
 */
int check_chars(char *code) {
    while (*code != '\0') {
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

    while (*code != '\0' && *(code + 1) != '\0') {
        somma += *code - '0';
        code++;
    }

    return somma % 10;
}

int main() {
    char code[MAX_SIZE + 2];
    int lunghezza = 0;
    int c;

    printf("Digita un codice: ");
    c = getchar();
    while (c != '\n' && c != EOF) {
        if (lunghezza <= MAX_SIZE) {
            code[lunghezza] = c;
            lunghezza++;
        }
        c = getchar();
    }
    code[lunghezza] = '\0';

    if (check_size(code) && check_chars(code) && get_crc(code) == code[lunghezza - 1] - '0') {
        printf("Codice valido\n");
    } else {
        printf("Codice non valido\n");
    }

    
}
