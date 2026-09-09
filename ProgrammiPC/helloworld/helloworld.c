
/**
 * @file helloworld.c
 * @brief Stampa "Hello, World!" per ogni numero primo da 1 a 999.
 * @name Marwan Salah
 * @date 05.09.2026
 */
#include <stdio.h>

int main(){
    for(int i = 1; i < 1000; i ++){

        int primo = 1;

        for (int j = 2; j < i; j++) {
            
            if (i % j == 0) {
                primo = 0;
            }           
        }

        if (primo) {
            printf("%03d Hello, World!\n", i);
        } 

    }
    
}

//sistemare header, implementare la funzione di controllo dei numeri primi, ogni funzione deve avere un commento doxygen.