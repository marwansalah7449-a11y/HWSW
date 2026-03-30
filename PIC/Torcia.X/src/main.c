//  ____    _    __  __   ____       _ _ _                            
// / ___|  / \  |  \/  | | __ )  ___| | (_)_ __  _______  _ __   __ _ 
// \___ \ / _ \ | |\/| | |  _ \ / _ \ | | | '_ \|_  / _ \| '_ \ / _` |
//  ___) / ___ \| |  | | | |_) |  __/ | | | | | |/ / (_) | | | | (_| |
// |____/_/   \_\_|  |_| |____/ \___|_|_|_|_| |_/___\___/|_| |_|\__,_|
//
//
// File:   main.c
// Author: Salah Marwan
// Description: sistema di controllo per una torcia
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

//define time constants
#define MS_REFRESH 10
#define FLASH_HALF_PERIOD 500 
#define DEBOUNCE_CYCLES 20
#define LONG_PRESS 1000

//define IO pins
#define H0 output_port.DOUT0
#define H1 output_port.DOUT1
#define SW1 sw_port.SW1
#define DL1 led_port.DL1

// define programs
#define OFF 0
#define PRG1 1
#define PRG2 2
#define PRG3 3
#define FLASH 4

//define general variables
uint8_t sw1_last = 1; //last state of sw1
uint8_t sw1_counter = 0; //counts the times sw1 changes its state
uint8_t sw1_stable = 1; //stable state of sw1(debounced)
uint16_t flash_counter = 0; //counter for FLASH mode
uint8_t cnt = 0; //pwm counter

uint8_t current_program = OFF; //current program
uint16_t button_press_counter = 0; // counts the cycles sw1 is pressed
bool button_pressed = false; 

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

void pwm_cycle(uint8_t duty) {
    if(cnt < duty/10){
        DL1 = 1;
    } else {
        DL1 = 0;
    }

    cnt++;
    if(cnt >= 10){
        cnt = 0;
    }
}

uint8_t choose_program(uint8_t sw1_stable){
    if (sw1_stable == 0) {
            if (!button_pressed) {
                button_pressed = true;
                
                button_press_counter = 0;
            }
            button_press_counter++;
        } else {
            if (button_pressed) {
                
                
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
                flash_counter = 0;
            }
            button_pressed = false;
        }
    return current_program;
}

void choose_pwm(uint8_t current_program){
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
                flash_counter++;
                if (flash_counter >= FLASH_HALF_PERIOD) {
                    flash_counter = 0;
                    DL1 = !DL1;
                }
                break;
        }
}

void main(void) {
    eh100_init();
    DL1 = 0;
    
    while (1) {
        debounce_sw1(); //debouncing sw1
               
        current_program = choose_program(sw1_stable); //save the current program
        
        choose_pwm(current_program); //sends the right pwm to the output(DL1)
        
        __delay_ms(1); //delay to estimate time with cycle counts

    }
}
