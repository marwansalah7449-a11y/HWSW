/*
 * File:   newmain.c
 * Author: gvs448
 *
 * Created on February 9, 2026, 1:26 PM
 */


#include "newxc8_header.h"

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
void main(void){
    TRISB = 0x0F;
    TRISD = 0x00;
    LATB = 0x00;
    while (1){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 100; j++){
                show_digit((i), 0);
                __delay_ms(FREQ_100HZ);
                show_digit((j/10), 1);
                __delay_ms(FREQ_100HZ);
            }
        }
       
    }
}
//
//void main(void) {
//    TRISB = 0x0F;
//    TRISD = 0x00;
//    LATB = 0x00;
//    LATD = 0x30;
//    
//    while (1) {
//        for(uint8_t i = 100; i < 1000; i++) {
//            
//            for(uint8_t j = 0; j<1000; j++){
//                LATD = (uint8_t)((LATD & 0xF0)|((j/100)&0x0F));
//                __delay_ms(10);
//                LATD = (uint8_t)(LATD ^ 0x60);
//                LATD = (uint8_t)((LATD & 0xF0)|((i/100)&0x0F));
//            }
//            
//            
//        }
//        
//    }
//}



//void main(void) {
//    TRISB = 0x0F;
//    TRISD = 0x00;
//    LATB = 0x00;
//    LATD = 0x52;
//    
//    while (1) {
//        
//        LATD = (uint8_t)(LATD ^ 0x66);
//        if(S1 == 1){
//            __delay_ms(500);
//        }else{
//            __delay_ms(1);
//        } 
//    }
//}

//void main(void) {
//    TRISB = 0x0F;
//    TRISD = 0x00;
//    LATB = 0x00;
//    LATD = 0x50;
//    
//    while (1) {
//        for(uint8_t i = 0; i < 10; i++) {
//            LATD = (uint8_t)(LATD ^ 0x60);
//            LATD = (uint8_t)((LATD & 0xF0)|(i&0x0F));
//            if(S1 == 1){
//                __delay_ms(500);
//            }else{
//                __delay_ms(10);
//            }
//            LATD = (uint8_t)(LATD ^ 0x60);
//            LATD = (uint8_t)((LATD & 0xF0)|(i&0x0F));
//            if(S1 == 1){
//                __delay_ms(500);
//            }else{
//                __delay_ms(10);
//            }
//        }
//        
//    }
//}

