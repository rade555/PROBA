/*
 * output_event.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Rade
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "usart.h"
#include "pin.h"
#include "timer0.h"
#include "output_event.h"


 /** Funkcija koja implementira num_of_repetitions perioda podizanja i spustanja vrednosti na pinu
  */
void pinPulsing(uint8_t port,uint8_t pin,uint32_t period,uint8_t num_of_repetitions) {
uint8_t i;
for(i = 0; i < num_of_repetitions; i++)
pinPulse(port,pin,period);

}



/** Funkcija koja implementira jedan treptaj diode odgovarajucom brzinom
 */
void pinPulse(uint8_t port,uint8_t pin,uint32_t period) {
//Poluperioda u kojoj pin ima visoku vrednost
pinSetValue(port,pin,HIGH);
timer0DelayMs(calculateHalfPeriod(period));


//Poluperioda u kojoj pin ima nisku vrednost
pinSetValue(port,pin,LOW);
timer0DelayMs(calculateHalfPeriod(period));

}





uint32_t calculateHalfPeriod(uint32_t period)
{
	return (period/2);
}




/** Funkcija koja preko serijskog porta ispisuje poruku u formatu "Transaction from {state} to {next_state}";
 * @param state,next_state- Trenutno stanje i naredno stanje
 * @return - Nema povratnu vrednost
 */

void logTran(state_t state,state_t next_state){
usartInit(9600);
usartPutString("Transaction from {state} to {next_state}");

}

/** Funkcija koja preko serijskog porta ispisuje poruku oblika "Time {mm}:{ss}.";
 * @param mm,sm
 * @return - Nema povratnu vrednost
 */
void logTime(uint16_t mm,uint16_t ss) {
usartInit(9600);
usartPutString("Time {mm}:{ss}");
}

/**Funkcija koja preko serijskog porta ispisuje poruku "Cutting"
 *@param - Nema
 *@return - Nema povratnu vrednost
 */
void logCut() {
usartInit(9600);
usartPutString("Cutting!");
}


/** Funkcija koja iskljucuje diodu na Arduino Uno Ploci
 * @param - Nema
 * @return - Nema povratnu vrednost
 */
void ledOff() {
pinInit(PORT_B,DIODE_PIN,OUTPUT);
pinSetValue(PORT_B, DIODE_PIN, LOW);
}



/** Funkcija koja ukjlucuje diodu na Arduino Uno Ploci
 * @param - Nema
 * @return - Nema povratnu vrednost
 */
void ledOn() {
pinInit(PORT_B,DIODE_PIN,OUTPUT);
pinSetValue(PORT_B, DIODE_PIN, HIGH);

}

/**Funkcija koja implementira jedan treptaj diode na Arduino UNO ploci sa poriodom od 1s
 * @param - Nema
 * @return - Nema povratnu vrednost
 */


/** Funkcija koja implementira jedan treptaj diode na Arduino UNO ploci sa periodom od 1s
 * @param - nema
 * @return - Nema povratnu vrednost
 */
void ledBlink() {
pinInit(PORT_B, DIODE_PIN, OUTPUT);
uint32_t period = 1000;
uint8_t num_of_repetitions = 1;
pinPulsing(PORT_B,DIODE_PIN,period,num_of_repetitions);
}





















