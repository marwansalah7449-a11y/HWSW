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


uint8_t sw1_last = 1;
uint8_t sw1_counter = 0;
uint8_t sw1_stable = 1;
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
    uint8_t on_time = duty_percent;
    uint8_t off_time = 100 - on_time;
    
    DL1 = 1;
    __delay_ms(on_time / 10);
    DL1 = 0;
    __delay_ms(off_time / 10);
}

void main(void) {
    eh100_init();
    DL1 = 0;
    
    uint8_t current_program = OFF;
    uint16_t button_press_counter = 0;
    bool button_pressed = false;
    bool button_released = false;
    
    while (1) {
        debounce_sw1();
        
        if (sw1_stable == 0) {
            if (!button_pressed) {
                button_pressed = true;
                button_released = false;
                button_press_counter = 0;
            }
            button_press_counter++;
        } else {
            if (button_pressed && !button_released) {
                button_released = true;
                
                if (button_press_counter >= LONG_PRESS) {
                    if (current_program == OFF) {
                        current_program = PRG1;
                    } else {
                        current_program = OFF;
                    }
                } else {
                    if (current_program != OFF) {
                        current_program = (current_program % 4) + 1;
                        if (current_program > 4) current_program = 1;
                    }
                }
            }
            button_pressed = false;
        }
        
        switch (current_program) {
            case OFF:
                DL1 = 0;
                break;
            case PRG1:
                DL1 = 1;
                break;
            case PRG2:
                pwm_cycle(50);
                break;
            case PRG3:
                pwm_cycle(10);
                break;
            case FLASH:
                DL1 = 1;
                __delay_ms(500);
                DL1 = 0;
                __delay_ms(500);
                break;
        }
        
        if (current_program == OFF || current_program == PRG1) {
            __delay_ms(MS_REFRESH);
        }
    }
}

