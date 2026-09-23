/**
 * @file StringExample.c
 * @brief trasforma qualsiasi stringa e la rende tutta in caratteri maiuscoli, poi la stampa.
 * @author Marwan Salah
 * @date 23.09.2026
 */

 #include <stdio.h>


 int main() {
    char str[] = "Hello, World";
    char *ptr = str;

    while(*ptr) {
        if (*ptr >= 'a' && *ptr <= 'z') {
            *ptr = *ptr - 32; 
        }
        ptr++;
    }
    printf("%s\n", str);
    
}
