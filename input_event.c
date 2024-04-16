#include <avr/io.h>
#include <stdint.h>
#include "input_event.h"



/** Funkcija koja proverava da li je pritisnut taster c na matricnj tastaturi.
 *@param - c
 *@return - Vrednost 1, ukoliko jeste, odnosno vrednost 0, ukoliko nije.
 */
uint8_t checkKeypad (int8_t c)
{


	uint8_t rows [4] = {11, 10, 9, 8};
	uint8_t cols [4] = {7, 6, 5, 4};
	uint8_t button;
	usartInit(9600);
	keypadInit(rows, cols);

	while(1)
	{
		button = keypadScan();
		if (button == 0xF2)
			return 1;
		else
			return 0;
	}

}

/** Funkcija koja proverava da li je potekla jedna sekunda od trenutka t0. Trenutak t0 je izrazen u broju mili sekundi proteklih od pokretanja tajmera 0.
 * @param - t0
 * @return - Vrednost 1, ukoliko jeste, odnosno vrednost 0, ukoliko nije.
 */
extern volatile unsigned long ms;

uint8_t secPass(uint32_t t0)

{
	timer0Init();
	uint32_t proteklo_vreme = ms;
	if((proteklo_vreme - t0) >= 1000)
		return 1;
	else
		return 0;

}
