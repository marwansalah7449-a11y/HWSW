/**
 * @file randomstring.c
 * @brief Genera una stringa di caratteri casuali di lunghezza definita e la stampa.
 * @author Marwan Salah
 * @date 13.10.2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Sceglie un carattere casuale tra lettere minuscole, maiuscole e cifre.
 *
 * @return il carattere scelto
 */
char get_random_char() {
    int n = rand() % 62;

    if (n < 26) {
        return 'a' + n;
    }
    if (n < 52) {
        return 'A' + (n - 26);
    }
    return '0' + (n - 52);
}

/**
 * @brief Crea una stringa di len caratteri casuali allocata dinamicamente.
 *
 * @param len numero di caratteri della stringa
 * @return la stringa creata, da liberare con free, oppure NULL se manca memoria
 */
char *get_random_str(size_t len) {
    char *str = malloc(len + 1);

    if (str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        str[i] = get_random_char();
    }
    str[len] = '\0';

    return str;
}

int main() {
    srand(time(NULL));

    char *str = get_random_str(10);
    if (str == NULL) {
        printf("Memoria insufficiente\n");
        return 1;
    }

    printf("%s\n", str);
    free(str);
}
