/*
 * File:   main.c
 * Author: marwansalah
 *
 * Created on February 19, 2026, 10:18 AM
 */

#include "config.h"


#define S0 PORTCbits.RC0
#define S1 PORTCbits.RC1
#define S2 PORTCbits.RC2
#define S3 PORTCbits.RC3


void show_digit(uint8_t digit, uint8_t disp){  
    LATD = (uint8_t)((((disp == 0) ? 0x30 : 0x50) & 0xF0) | (digit & 0x0F));
}

void main(void) {
    uint8_t lastS0 = 1;
    uint8_t counter = 0;
    
    TRISC = 0xFF; 
    TRISD = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELD = 0x00; //disabilita ingressi analogici(quando non funziona input)
    while (1){
        
        if (!S0 && lastS0){
            counter++;
            if (counter >= 10){
                counter = 0;
            }
        }
        lastS0 = S0;

        show_digit(counter, 1);    
    }
}
