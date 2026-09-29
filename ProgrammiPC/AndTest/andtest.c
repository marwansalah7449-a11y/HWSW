/**
 * @file andtest.c
 * @brief Verifica il comportamento dell'operatore logico AND in C.
 * @author Marwan Salah
 * @date 29.09.2026
 */
#include <stdio.h>

int prima_condizione() {
	printf("Valuto la prima condizione\n");
	return 0;
}

int seconda_condizione() {
	printf("Valuto la seconda condizione\n");
	return 1;
}

int main() {
	if (prima_condizione() && seconda_condizione()) {
		printf("Entrambe vere\n");
	} else {
		printf("Non sono entrambe vere\n");
	}

}