/*
 * File:   main.c
 * Author: gvs448
 *
 * Created on February 9, 2026, 3:21 PM
 */

#include "config.h"

// Define Button and LED connections
#define LD1 LATBbits.LB4
#define LD2 LATBbits.LB5
#define LD3 LATBbits.LB6
#define LD4 LATBbits.LB7
#define S1 PORTBbits.RB0
#define S2 PORTBbits.RB1
#define S3 PORTBbits.RB2
#define S4 PORTBbits.RB3

#define _XTAL_FREQ (16000000)
#define LED_MASK 0b11110000
#define FREQ_100HZ 10

void show_digit(uint8_t digit, uint8_t disp){  
        LATD = (uint8_t)((((disp == 0) ? 0x30 : 0x50) & 0xF0)|(digit & 0x0F));
        
    
}


void main(void) {
    TRISB = 0x0F;
    TRISD = 0x00;
    LATB = 0x00;
    uint8_t lastS1 = 1;
    uint8_t lastS2 = 1;
    while (1){
        for(uint8_t i = 0; i < 10; i++){
            for(uint8_t j = 0; j < 10;){
                if (S1 && !lastS1){ 
                    j++;  
                }
                lastS1 = S1;
                if (S2 && !lastS2) {
                    if (j > 0) {
                        j--;
                    } else {
                        j = 9;
                        if (i > 0) {
                            i--;
                        } else {
                            i = 9;  
                        }
                    }
                }
                lastS2 = S2;

                show_digit((i), 0);
                __delay_ms(FREQ_100HZ);
                show_digit((j), 1);
                __delay_ms(FREQ_100HZ);
            }
        }
       
    }
}
