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
#define SB0 PORTCbits.RC0
#define SB1 PORTCbits.RC1

#define _XTAL_FREQ (16000000)
#define LED_MASK 0b11110000
#define FREQ_100HZ 3

#define DEBOUNCE_CYCLES 3   
uint8_t S1_stable = 1;   
uint8_t last1_old = 1;   
uint8_t counter1 = 0;    
uint8_t S2_stable = 1;   
uint8_t last2_old = 1;   
uint8_t counter2 = 0;  
#define SEQ (0xAA11AEB16ADD67DALLU)
void show_digit(uint8_t digit, uint8_t disp){  
        LATD = (uint8_t)((((disp == 0) ? 0x30 : 0x50) & 0xF0)|(digit & 0x0F));
}

void debounce_S(uint8_t S, uint8_t N){
    if(N == 0){
        if(S != last1_old){
            last1_old = S;
            counter1 = 0;
        } else {
            if(counter1 < DEBOUNCE_CYCLES){
                counter1++;
            }
            if(counter1 >= DEBOUNCE_CYCLES){
                S1_stable = last1_old;
            }
        }
    }else{    
        if(S != last2_old){
            last2_old = S;
            counter2 = 0;
        }else{
            if(counter2 < DEBOUNCE_CYCLES){
                counter2++;
            }
            if(counter2 >= DEBOUNCE_CYCLES){
                S2_stable = last2_old;
            }
        }
    }
}

void main(void) {
    TRISB = 0x0F;
    TRISD = 0x00;
    LATB = 0x00;
    uint8_t counter = 0;
    while (1){
        
        
        
        uint8_t p = (2 * SB1) + SB0;
        
        uint8_t val = (SEQ >> (48 - (p*16)+4*(3-counter))) & 0x0F;
        show_digit(val, (counter & 1));
        __delay_ms(FREQ_100HZ);
        counter = (counter + 1) % 4;
       
        
//        if (SB0 == 0 && SB1 == 0) {
//            show_digit(1, 1);
//            __delay_ms(FREQ_100HZ);
//            show_digit(10, 1);
//            __delay_ms(FREQ_100HZ);
//            show_digit(1, 0);
//            __delay_ms(FREQ_100HZ);
//            show_digit(10, 0);
//            __delay_ms(FREQ_100HZ);
//        }else if (SB0 == 0 && SB1 == 1) {
//            show_digit(5, 0);
//            __delay_ms(FREQ_100HZ);
//            show_digit(10, 0);
//            __delay_ms(FREQ_100HZ);
//            show_digit(13, 1);
//            __delay_ms(FREQ_100HZ);
//            show_digit(10, 1);
//            __delay_ms(FREQ_100HZ);
//        }else if (SB0 == 1 && SB1 == 0) {
//            show_digit(11, 0);
//            __delay_ms(FREQ_100HZ);
//            show_digit(10, 0);
//            __delay_ms(FREQ_100HZ);
//            show_digit(6, 1);
//            __delay_ms(FREQ_100HZ);
//            show_digit(12, 1);
//            __delay_ms(FREQ_100HZ);
//        }else if (SB0 == 1 && SB1 == 1) {
//            show_digit(5, 0);
//            __delay_ms(FREQ_100HZ);
//            show_digit(10, 0);
//            __delay_ms(FREQ_100HZ);
//            show_digit(7, 1);
//            __delay_ms(FREQ_100HZ);
//            show_digit(10, 1);
//            __delay_ms(FREQ_100HZ);
//        }

    }
}
