/*
 * File:   main.c
 * Author: gvs448
 *
 * Created on 26. gennaio 2026, 14:55
 */



#include "config.h"
#define LD1 LATBbits.LB4 
#define LD2 LATBbits.LB5
#define LD3 LATBbits.LB6
#define LD4 LATBbits.LB7
#define S1 PORTBbits.RB0
#define S4 PORTBbits.RB3
#define S2 PORTBbits.RB1
#define S3 PORTBbits.RB2
#define _XTAL_FREQ (16000000)
void main(void) {
    TRISB = 0x0F;
    LATB = 0; 
    while(1){ 
        LATB = LATB ^ (~PORTB << 4);
        __delay_ms(500);
    }
} 
