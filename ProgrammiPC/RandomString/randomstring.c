/**
 * @file randomstring.c
 * @brief Genera una stringa di caratteri casuali di lunghezza definita e la stampa.
 * @author Marwan Salah
 * @date 06.10.2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

char caratteri[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/**
 * @brief Crea una stringa di len caratteri casuali (lettere minuscole, maiuscole e cifre).
 *
 * @param len numero di caratteri della stringa (al massimo MAX_SIZE)
 * @return la stringa creata
 */
char *get_random_str(size_t len) {
    static char str[MAX_SIZE + 1];

    if (len > MAX_SIZE) {
        len = MAX_SIZE;
    }

    for (size_t i = 0; i < len; i++) {
        str[i] = caratteri[rand() % 62];
    }
    str[len] = '\0';

    return str;
}

int main() {
    srand(time(NULL));
    printf("%s\n", get_random_str(10));
}
