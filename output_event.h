/*
 * output_event.h
 *
 *  Created on: Apr 16, 2024
 *      Author: Rade
 */

#ifndef OUTPUT_EVENT_H_
#define OUTPUT_EVENT_H_

#include <avr/io.h>
#include <stdint.h>








typedef enum {state,next_state}state_t;

///Deklaracija funkcije logTran koja ce biti definisana fajlu output_event.c
void logTran(state_t state,state_t next_state);

///Deklaracija funkcije logTime koja ce biti definisana u fajlu output_event.c
void logTime(uint16_t mm,uint16_t ss);

///Deklaracija funkcije logCut koja ce biti definisana u fajlu output_event.c
void logCut();


///Deklaracija funkcije ledOff koja ce biti definisana u fajlu output_event.c
void ledOff();

///Deklaracija funkcije ledOn koja ce biti definisana u fajlu output_event.c
void ledOn();









///Deklaracija pinPulsing
void pinPulsing(uint8_t port, uint8_t pin, uint32_t period, uint8_t num_of_repetitions);

///Deklaracija pinPulse
void pinPulse (uint8_t port, uint8_t pin, uint32_t period);

///Deklaracija calculateHalfPeriod
uint32_t calculateHalfPeriod(uint32_t period);





///Deklaracija funkcije ledOn koja ce biti definisana u fajlu output_event.c
void ledBlink();


#endif /* OUTPUT_EVENT_H_ */























