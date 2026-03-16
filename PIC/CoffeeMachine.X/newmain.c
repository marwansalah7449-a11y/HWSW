
#include <xc.h>

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


void led_rotator() {
    unsigned char leds = 0x01;

  
    LATB = 0x00;

    while (1) {
        LATB = (LATB & 0x0F) | (leds << 4);

    
        if (S1 == 0) {
            leds = (leds >> 1) | (leds << 3);
        } else {
            leds = (leds << 1) | (leds >> 3);
        }

        leds &= 0x0F;
        __delay_ms(500);
    }
}

void led_counter() {
    LATB = 0;

    unsigned char buttons;
    unsigned char count;
    unsigned char i;
    unsigned char leds;

    while (1) {
   
        buttons = ~PORTB & 0x0F;

        count = 0;
        for (i = 0; i < 4; i++) {
            if (buttons & (1 << i)) {
                count++;
            }
        }
        leds = 0;
        for (i = 0; i < count; i++) {
            leds = leds | (1 << (4 + i)); // Shift to RB4-RB7
        }
        LATB = (LATB & 0x0F) | leds;
        __delay_ms(20);
    }
}

void led_blinker() {
    LATB = 0x00;

    while (1) {
    
        LATB = (uint8_t)(LATB ^ ((~PORTB) << 4));

        __delay_ms(500);
    }
}

void main(void) {
  
   
    TRISB = 0x0F;  

  
    __delay_ms(100);



    if (S2 == 0) { 
        led_rotator();
    } else if (S3 == 0) { 
        led_counter();
    } else {
        led_blinker();
    }

  
}
