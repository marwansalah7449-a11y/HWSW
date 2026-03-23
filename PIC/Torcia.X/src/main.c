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

#define DEBOUNCE_CYCLES 3
#define LONG_PRESS 100


#define H0 output_port.DOUT0
#define H1 output_port.DOUT1
#define SW1 sw_port.SW1
#define DL1 led_port.DL1

#define OFF 0
#define PRG1 1
#define PRG2 2
#define PRG3 3
#define FLASH 4

#define FLASH_HALF_PERIOD 50   

uint32_t cnt = 0;
uint8_t sw1_last = 1;
uint8_t sw1_counter = 0;
uint8_t sw1_stable = 1;
uint8_t flash_counter = 0;
////////////////////////////////////////////////////////////////////////////////
// private functions
////////////////////////////////////////////////////////////////////////////////
void debounce_sw1(void) {
    if (SW1 != sw1_last) {
        sw1_last = SW1;
        sw1_counter = 0;
    } else {
        if (sw1_counter < DEBOUNCE_CYCLES) {
            sw1_counter++;
        }
        if (sw1_counter >= DEBOUNCE_CYCLES) {
            sw1_stable = sw1_last;
        }
    }
}


void pwm_cycle(uint8_t duty_percent) {
    if(cnt % 100 == 0){
        DL1 = 1;
    }else if(cnt % 100 == duty_percent){
        DL1 = 0;
    }
    if(cnt >= 100000000){
        cnt = 0;
    }
}
void main(void) {
    eh100_init();
    DL1 = 0;
    
    while(1){
        pwm_cycle(10);
        cnt++;
    }
}

