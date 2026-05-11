//  ____    _    __  __   ____       _ _ _                            
// / ___|  / \  |  \/  | | __ )  ___| | (_)_ __  _______  _ __   __ _ 
// \___ \ / _ \ | |\/| | |  _ \ / _ \ | | | '_ \|_  / _ \| '_ \ / _` |
//  ___) / ___ \| |  | | | |_) |  __/ | | | | | |/ / (_) | | | | (_| |
// |____/_/   \_\_|  |_| |____/ \___|_|_|_|_| |_/___\___/|_| |_|\__,_|
//
//
// @file main.c
// @author Salah Marwan
// @date 11.05.2026
// @brief gioco whac a mole
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
//1 ciclo = ~ 2 * MS_REFRESH
#define MS_REFRESH 1
#define DEBOUNCE_CYC 30 // 60ms

#define MAX_MATCH 15
#define MAX_SCORE 75

#define MAX_ACTIVE_T 1500 // 3000ms

#define ACTIVE_T_DECR 10 // 20ms
#define SCORE_INCR 5
#define MAX_RND_T 350 // 700ms
#define MIN_RND_T 250 // 500ms


#define ST_W_COIN 0
#define ST_W_START 1
#define ST_W_RND 2
#define ST_W_HAMMER 3
#define ST_WIN_MATCH 4
#define ST_LOOSE_MATCH 5
#define ST_MATCH_END 6
#define ST_END_GAME 7

#define S0 input_port.DIN0

#define DL1 led_port.DL1
#define DL2 led_port.DL2
#define DL3 led_port.DL3
#define DL4 led_port.DL4
////////////////////////////////////////////////////////////////////////////////
// private functions
////////////////////////////////////////////////////////////////////////////////

// dot = 0 --> acceso
void show_digit(uint8_t digit, uint8_t disp, uint8_t dot){ 
    if(dot){
        LATD = (uint8_t)((((disp == 0) ? 0x30 : 0x50) & 0xF0)|(digit & 0x0F));
    }else{
        LATD = (uint8_t)((((disp == 0) ? 0x20 : 0x40) & 0xF0)|(digit & 0x0F));
    }          
}

void show_score(uint8_t score){
    uint8_t decinaScore = score / 10; 
    uint8_t unitaScore = score % 10;   
    show_digit(decinaScore, 0, 1);
    __delay_ms(MS_REFRESH);
    show_digit(unitaScore, 1, 1);
    __delay_ms(MS_REFRESH);
}

void random_mole() {
    uint8_t x =  rand() % (1 - 4 + 1) + 1;
    switch(x){
        case 1:
            DL1 = 1;
            DL2 = DL3 = DL4 = 0;
            break;
        case 2:
            DL2 = 1;
            DL1 = DL3 = DL4 = 0;
            break;
        case 3:
            DL3 = 1;
            DL1 = DL2 = DL4 = 0;
            break;
        case 4:
            DL4 = 1;
            DL1 = DL2 = DL3 = 0;
            break;
            
    }
}

void random_wait() {
    __delay_ms(rand() % (MIN_RND_T - MAX_RND_T + 1) + MIN_RND_T);
}

uint8_t SW_check() {
    uint8_t count = 0;
    while (sw_port.SWITCHES > 0) {
        if (sw_port.SWITCHES & 1){
            count++;
        }
        sw_port.SWITCHES >>= 1;
    }
    if(count>1){
        return 0;
    }else{
        return 1;
    }
    
}



void main(){
	// init hardware
	eh100_init();
    uint8_t score = 0;
    uint8_t match = 0;
    uint8_t state = 0;
    uint16_t activeTime = MAX_ACTIVE_T;
    uint8_t activeTimeCnt = 0;
    DL1 = DL2 = DL3 = DL4 = 0;

	// main loop
    while(1){     

        switch(state){
            case ST_W_COIN:            
                if(S0){
                    show_score(score);
                    state = ST_W_START;
                    break;
                }
            case ST_W_START:               
                score = 0;
                if(!S0){
                    state = ST_W_RND;
                    break;
                }
            case ST_W_RND:
                random_wait();
                random_mole();
                state = ST_W_HAMMER;
                break;
                
            case ST_W_HAMMER:
                activeTimeCnt++;
                if(activeTimeCnt >= activeTime){                   
                    state = ST_LOOSE_MATCH;
                    activeTimeCnt = 0;
                    break;
                }else if (sw_port.SWITCHES == led_port.LED && SW_check()){                    
                    activeTimeCnt = 0;
                    state = ST_WIN_MATCH;
                    break;                    
                }
            case ST_LOOSE_MATCH:
                match++;
                state = ST_MATCH_END;
                break;
            case ST_WIN_MATCH:
                match++;
                score = score + SCORE_INCR;
                activeTime = activeTime - ACTIVE_T_DECR;
                state = ST_MATCH_END;
                break;
            case ST_MATCH_END:
                if(score >= MAX_SCORE || match >= MAX_MATCH){
                    state = ST_END_GAME;
                    break;
                }else{
                    state = ST_W_RND;
                    break;
                }
            case ST_END_GAME:
               show_score(score);              
               DL1 = DL2 = DL3 = DL4 = 0;
               activeTime = MAX_ACTIVE_T;
               if(S0){                  
                   state = ST_W_COIN;
                   break;
               }
        }
        
        
    }
}