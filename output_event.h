#include <avr/io.h>
#include <stdint.h>

#ifndef OUTPUT_EVENT_H_
#define OUTPUT_EVENT_H_

typedef enum {state, next_state}state_t;

void logTran(state_t state, state_t next_state);

void logTime (uint16_t mm, uint16_t ss);

void logCut();

void ledOff();

void ledOn();

void ledBlink();

void pinPulsing(uint8_t port, uint8_t pin, uint32_t period, uint8_t num_of_repetitions);

void pinPulse(uint8_t port, uint8_t pin, uint32_t period);

uint32_t calculateHalfPeriod(uint32_t period);

#endif /* OUTPUT_EVENT_H_ */
