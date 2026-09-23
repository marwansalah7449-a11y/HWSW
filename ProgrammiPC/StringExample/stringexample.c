/**
 * @file StringExample.c
 * @brief trasforma qualsiasi stringa e la rende tutta in caratteri maiuscoli, poi la stampa.
 * @author Marwan Salah
 * @date 23.09.2026
 */

 #include <stdio.h>

bool is_lower(char c) {
    return (c >= 'a' && c <= 'z');
}

char to_upper(char c) {
    if (is_lower(c)) {
        return c - 32;
    }
    return c;
}

 int main() {
    char str[] = "Hello, World";
    char *ptr = str;

    while(*ptr) {
       printf("%c", to_upper(*ptr));
       ptr++;
    }
    printf("\n");

}
