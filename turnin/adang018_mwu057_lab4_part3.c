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

enum States {Init, Wait, Press_Pound, Pound, Unlock} state;
unsigned char xButton;
unsigned char yButton;
unsigned char poundButton;
unsigned char lockButton;
unsigned char isUnlocked;

void Tick();

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    state = Init;
    isUnlocked = 0;

    while (1) {
        xButton = (PINA & 0x01);
        yButton = (PINA & 0x02);
        poundButton = (PINA & 0x04);
        lockButton = (PINA & 0x80);
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
            if(!xButton && !yButton && poundButton) {
                state = Press_Pound;
            } else {
                state = Wait;
            }
            break;
        case Press_Pound:
	    if(!xButton && !yButton && poundButton) {
                state = Press_Pound;
            } else if(!xButton && !yButton && !poundButton) {
                state = Pound;
            } else {
                state = Wait;
            }
            break;
        case Pound:
            if(!xButton && !yButton && !poundButton) {
                state = Pound;
            } else if(!xButton && yButton && !poundButton) {
                state = Unlock;
            } else {
                state = Wait;
            }
            break;
        case Unlock:
            if(lockButton) {
                state = Wait;
            } else {
                state = Unlock;
            }
            break;
        default:
	    state = Init;
            break;
    }
    // State actions
    switch(state) {
        case Init:
	    isUnlocked = 0;
	    break;
        case Wait:
            isUnlocked = 0;
            break;
        case Press_Pound:
            isUnlocked = 0;
 	    break;
        case Pound:
            isUnlocked = 0;
            break;
        case Unlock:
	    isUnlocked = 1;
	    break;
        default:
            isUnlocked = 0;
	    break;
    }
    PORTB = isUnlocked;
}
