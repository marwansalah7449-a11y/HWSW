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
#include <stdlib.h>
#include <xc.h>
////////////////////////////////////////////////////////////////////////////////
// constants
////////////////////////////////////////////////////////////////////////////////
//1 ciclo = ~ MS_REFRESH
#define MS_REFRESH 1
#define DEBOUNCE_CYC 30 // 60ms

#define MAX_MATCH 15
#define MAX_SCORE 75

#define MAX_ACTIVE_T 1100 // ~3000ms reali in ST_W_HAMMER (numero trovato a tentativi)

#define ACTIVE_T_DECR 7 // ~20ms reali in ST_W_HAMMER per ogni punto fatto
#define SCORE_INCR 5
#define MAX_RND_T 700 // 700ms
#define MIN_RND_T 500 // 500ms


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


// SW_PRESSED restituisce il pattern dei pulsanti premuti 
#define SW_PRESSED  ((uint8_t)((~sw_port.SWITCHES) & 0x0F))
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
    uint8_t x = rand() % (4 - 1 + 1) + 1;
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

void random_wait(uint8_t score) {
    uint16_t ms = rand() % (MAX_RND_T - MIN_RND_T + 1) + MIN_RND_T;
    // ogni show_score dura ~2 * MS_REFRESH (= 2ms), quindi incremento s di 2
    for (uint16_t s = 0; s < ms; s += 2){
        show_score(score);
    }
}

// ritorna 1 solo se un solo pulsante è premuto 
uint8_t SW_check() {
    uint8_t count = 0;
    uint8_t tmp = SW_PRESSED; 
    while (tmp > 0) {
        if (tmp & 1){
            count++;
        }
        tmp >>= 1;
    }
    return (count == 1) ? 1 : 0;
}



void main(){
	// init hardware
	eh100_init();
    uint8_t score = 0;
    uint8_t match = 0;
    uint8_t state = ST_W_COIN;
    uint16_t activeTime = MAX_ACTIVE_T;
    uint16_t activeTimeCnt = 0;
    uint16_t seed = 0;
    DL1 = DL2 = DL3 = DL4 = 0;

	// main loop
    while(1){     

        switch(state){
            case ST_W_COIN:
                DL1 = DL2 = DL3 = DL4 = 0;
                seed++; 
                if(S0){
                    srand(seed);
                    score = 0;
                    match = 0;
                    activeTime = MAX_ACTIVE_T;
                    state = ST_W_START;
                }
                break;
                
            case ST_W_START:
                show_score(score);
                if(!S0){
                    state = ST_W_RND;
                }
                break;
                
            case ST_W_RND:
                __delay_ms(10);
                DL1 = DL2 = DL3 = DL4 = 0;
                random_wait(score);
                random_mole();
                
                state = ST_W_HAMMER;
                break;
                
            case ST_W_HAMMER:
                activeTimeCnt++;
                show_score(score); 
                if(activeTimeCnt >= activeTime){
                    activeTimeCnt = 0;
                    state = ST_LOOSE_MATCH;
                }else if (SW_PRESSED == led_port.LED && SW_check()){
                    activeTimeCnt = 0;
                    state = ST_WIN_MATCH;
                }else if (SW_check()){
                    activeTimeCnt = 0;
                    state = ST_LOOSE_MATCH;
                }
                break;
                
            case ST_LOOSE_MATCH:
                match++;
                state = ST_MATCH_END;
                break;
                
            case ST_WIN_MATCH:
                DL1 = DL2 = DL3 = DL4 = 1;
                
                match++;
                score = score + SCORE_INCR;
                // -20ms per ogni punto fatto
                activeTime = activeTime - (ACTIVE_T_DECR * SCORE_INCR);
                state = ST_MATCH_END;
                break;
                
            case ST_MATCH_END:
                if(score >= MAX_SCORE || match >= MAX_MATCH){
                    state = ST_END_GAME;
                }else{
                    state = ST_W_RND;
                }
                break;
                
            case ST_END_GAME:
                DL1 = DL2 = DL3 = DL4 = 0;
                show_score(score);
                if(S0){
                    state = ST_W_COIN;
                }
                break;
        }
        
        
    }
}