/*	Author: Albert Dang adang018@ucr.edu
 *      Partner(s) Name: Min-Hua Wu mwu057@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Init, Wait, Inc, Press_Inc, Dec, Press_Dec, Zero} state;
unsigned incButton;
unsigned decButton;
unsigned char counter;

void Tick();

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    
    state = Init;
    incButton = (PINA & 0x01);
    decButton = (PINA & 0x02);
    counter = 7;

    while (1) {
        incButton = (PINA & 0x01);
        decButton = (PINA & 0x02);
        Tick();
    }
    return 1;
}

void Tick() {
    // State transitions
    switch(state) {
        case Init: 
            state = Wait;
            break;
        case Wait:
	    if(!incButton && !decButton) {
	        state = Wait;
	    } else if(incButton && !decButton){
	        state = Inc;
	    } else if(!incButton && decButton) {
	        state = Dec;
	    } else if(incButton && decButton) {
                state = Zero;
            }
            break;
        case Inc:
	    state = Press_Inc;
            break;
        case Press_Inc:
	    if(!incButton) {
                state = Wait;
	    } else if(incButton && !decButton) {
	        state = Press_Inc;
	    } else if(incButton && decButton) {
                state = Zero;
            }
	    break;
        case Dec:
            state = Press_Dec;
            break;
        case Press_Dec:
            if(!decButton) {
                state = Wait;
            } else if(!incButton && decButton) {
                state = Press_Dec;
            } else if(incButton && decButton) {
                state = Zero;
            }
            break;
        case Zero:
            state = Wait;
            break;
        default:
	    state = Init;
            break;
    }
    // State actions
    switch(state) {
        case Init:
	    counter = 7;
	    break;
        case Wait:
            break;
        case Inc:
            if(counter < 9) {
	        counter += 1;
            }
 	    break;
        case Press_Inc:
            break;
        case Dec:
	    if(counter > 0) {
                counter -= 1;
            }
	    break;
        case Press_Dec:
            break;
        case Zero:
            counter = 0;
            break;
        default:
            counter = 7;
	    break;
    }
    PORTC = counter;
}
