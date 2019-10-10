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

enum States {Init, PB0_On, Press_PB1_On, PB1_On, Press_PB0_On} state;
unsigned char button = 0x00;
unsigned char led = 0x00;

void Tick();

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    state = Init;
    led = 0x01;

    while (1) {
        button = (PINA & 0x01);
        Tick();
    }
    return 1;
}

void Tick() {
    // State transitions
    switch(state) {
        case Init: 
            state = PB0_On;
            break;
        case PB0_On:
	    if(button == 1) {
	        state = Press_PB1_On;
	    } else {
	        state = PB0_On;
	    }
            break;
        case Press_PB1_On:
            if(button == 0) {
	        state = PB1_On;
	    } else {
	        state = Press_PB1_On;
	    }
            break;
        case PB1_On:
	    if(button == 1) {
                state = Press_PB0_On;
	    } else {
	        state = PB1_On;
	    }
	    break;
        case Press_PB0_On:
	    if(button == 0) {
	        state = PB0_On;
            } else {
 	        state = Press_PB0_On;
	    }
            break;
        default:
	    state = Init;
            break;
    }
    // State actions
    switch(state) {
        case Init:
	    led = 0x01;
	    break;
        case PB0_On:
	    led = 0x01;
            break;
        case Press_PB1_On:
	    led = 0x02;
 	    break;
        case PB1_On:
            led = 0x02;
            break;
        case Press_PB0_On:
	    led = 0x01;
	    break;
        default:
            led = 0x01;
	    break;
	    
    }
    PORTB = led;
}
