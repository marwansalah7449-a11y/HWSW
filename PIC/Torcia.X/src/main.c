//  ____    _    __  __   ____       _ _ _                            
// / ___|  / \  |  \/  | | __ )  ___| | (_)_ __  _______  _ __   __ _ 
// \___ \ / _ \ | |\/| | |  _ \ / _ \ | | | '_ \|_  / _ \| '_ \ / _` |
//  ___) / ___ \| |  | | | |_) |  __/ | | | | | |/ / (_) | | | | (_| |
// |____/_/   \_\_|  |_| |____/ \___|_|_|_|_| |_/___\___/|_| |_|\__,_|
//
//
// File:   main.c
// Author: Salah Marwan
// Description:
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// application includes
////////////////////////////////////////////////////////////////////////////////
#include "eh100.h"

////////////////////////////////////////////////////////////////////////////////
// system includes
////////////////////////////////////////////////////////////////////////////////
#include <stdbool.h>
#include <stdint.h>
#include <xc.h>


////////////////////////////////////////////////////////////////////////////////
// constants
////////////////////////////////////////////////////////////////////////////////
#define MS_REFRESH 10
#define H0 output_port.DOUT0
#define H1 output_port.DOUT1
#define SW1 sw_port.SW1
#define DL1 led_port.DL1

////////////////////////////////////////////////////////////////////////////////
// private functions
////////////////////////////////////////////////////////////////////////////////
void PRG1(){
    DL1 = 1;
}
void PRG2(){
    DL1 = 1;
    __delay_ms(5);
    DL1 = 0;
    __delay_ms(5);
}
void PRG3(){
    DL1 = 1;
    __delay_ms(1);
    DL1 = 0;
    __delay_ms(9);
}
void FLASH(){
    DL1 = 1;
    __delay_ms(500);
    DL1 = 0;
    __delay_ms(500);
}


void main(){
    eh100_init();
    DL1 = 0;
    
    uint8_t program = 0;  
    uint8_t lastSW1 = 1;
    uint16_t SW1Counter = 0;
    bool buttonReleased = false;
    
    while (1) {
        
        
        if (SW1 == 0) { 
            SW1Counter++;
            buttonReleased = false;
        } else {  
            if (SW1Counter > 0 && !buttonReleased) {
               
                if (SW1Counter >= 100) {
                    program = (program == 0) ? 1 : 0;  
                } else {
                    
                    if (program != 0) {
                        program = (program % 4) + 1;  
                    }
                }
            }
            SW1Counter = 0;
            buttonReleased = true;
        }
        
        
        switch (program) {
            case 0:
                DL1 = 0;
                break;
            case 1:
                PRG1();
                break;
            case 2:
                PRG2();
                break;
            case 3:
                PRG3();
                break;
            case 4:
                FLASH();
                break;
        }
        __delay_ms(10);
      }
}

