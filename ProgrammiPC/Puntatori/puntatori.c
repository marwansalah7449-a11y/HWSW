/**
 * @file puntatori.c
 * @brief Legge e stampa gli indirizzi di memoria di alcune variabili.
 * @author Marwan Salah
 * @date 15.09.2026
 */

 #include <stdio.h>



 int main(void) {
    int a = 10;
    double b = 20.5;
    char c = 'Z';
    char *p = &c;

    printf("Indirizzo di a: %p\n", &a);
    printf("Indirizzo di b: %p\n", &b);
    printf("Indirizzo di c: %p\n", &c);
    printf("Indirizzo di p: %p\n", &p);

 }