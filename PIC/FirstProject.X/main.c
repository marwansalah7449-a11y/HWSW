 /*
 * @File: main.c
 * @Author: Marwan Salah
 * @Brief: fa una rotazione dei Led e cambia direzione premendo S1
 * @Date: 19.1.2026
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

    unsigned char leds = 0x01; 

    while (1){
       
        LATB = (LATB & 0x0F) | (leds << 4);

        if (S1){
            
            leds = (leds >> 1) | (leds << 3);
        }else{   
            
            leds = (leds << 1) | (leds >> 3);
        }

        
        leds &= 0x0F;

        __delay_ms(500);
    }
}

