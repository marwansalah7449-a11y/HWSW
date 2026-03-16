#ifndef __EH100_H__
#define	__EH100_H__


////////////////////////////////////////////////////////////////////////////////
// application includes
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// system includes
////////////////////////////////////////////////////////////////////////////////
#include <stdbool.h>
#include <stdint.h>



////////////////////////////////////////////////////////////////////////////////
// constants
////////////////////////////////////////////////////////////////////////////////
// Registers init values
#define TRISC_INIT  0xff
#define TRISD_INIT  0x00
#define TRISB_INIT  0x0f
#define ANSEL_INIT  0x00

// Oscillator frequency (needed by delay functions)
#define _XTAL_FREQ 20000000



////////////////////////////////////////////////////////////////////////////////
// typedefs
////////////////////////////////////////////////////////////////////////////////

//--- GPI bitfield definitions -------------------------------------------------
typedef union {
    struct {
        unsigned DIN0  :1;
        unsigned DIN1  :1;
        unsigned DIN2  :1;
        unsigned DIN3  :1;
        unsigned DIN4  :1;
        unsigned DIN5  :1;
        unsigned DIN6  :1;
        unsigned DIN7  :1;
    };
    struct {
        unsigned DIN   :8;
    };
} input_port_t;
extern volatile input_port_t input_port __at(0xF82); // PORTC

//--- GPO bitfield definitions -------------------------------------------------
typedef union {
    struct {
        unsigned DOUT0 :1;
        unsigned DOUT1 :1;
        unsigned DOUT2 :1;
        unsigned DOUT3 :1;
        unsigned DOUT4 :1;
        unsigned DOUT5 :1;
        unsigned DOUT6 :1;
        unsigned DOUT7 :1;
    };
    struct {
        unsigned DOUT  :8;
    };
} output_port_t;
extern volatile output_port_t output_port __at(0xF8C); // LATD

//--- Onboard LEDs bitfield definitions ----------------------------------------
typedef union {
    struct {
        unsigned       :4;
        unsigned DL1   :1;
        unsigned DL2   :1;
        unsigned DL3   :1;
        unsigned DL4   :1;
    };
    struct {
        unsigned       :4;
        unsigned LED   :4;
    };
} led_port_t;
extern volatile led_port_t led_port __at(0xF8A); // LATB

//--- Onboard switches bitfield definitions ------------------------------------
typedef union {
    struct {
        unsigned SW1      :1;
        unsigned SW2      :1;
        unsigned SW3      :1;
        unsigned SW4      :1;
        unsigned          :4;
    };
    struct {
        unsigned SWITCHES :4;
        unsigned          :4;
    };
} sw_port_t;
extern volatile sw_port_t sw_port __at(0xF81); // PORTB



////////////////////////////////////////////////////////////////////////////////
// macros
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// prototypes
////////////////////////////////////////////////////////////////////////////////

void eh100_init();


#endif	// __EH100_H__

