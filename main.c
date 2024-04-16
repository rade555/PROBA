


/**
* @file main.c
* @brief Zadatak
* @author Radenko Vasic
* @date 4.14.2024
* @version 1.0
 */


#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include "keypad.h"
#include "pin.h"
#include "timer0.h"
#include <stdint.h>
#include "output_event.h"





/**
 * Funkcija koja proverava da li je pritisnut taster c na matricnoj tastaturi
 * @param c- Ulaz tipa int8_t koji je zapravo taster c
 * @return - Vrednost 1,ukoliko jeste,odnosno vrednost 0 ukoliko nije
 *
 */
uint8_t checkKeypad(int8_t c) {

uint8_t rows[4] = {11,10,9,8};
uint8_t cols[4] = {7,6,5,4};

uint8_t button;
usartInit(9600);
keypadInit(rows,cols);
while(1)
{
button = keypadScan();

if (button == 0xF2)
{
return 1;
}
else
{
return 0;
}
}
}





/**Funkcija za rad sa prekidima
 *
 */
	void timer0Init()
	{
		//tajmer0 u CTC mood
		TCCR0A = 0x02;

		//provera frekvencije takta tokom kompilacije
		#if F_CPU > 20000000
		#error "Frekvencija takta mora biti manja od 20MHz"
		#endif

		//incijalizacija promenljivih za preskaler i periodu
		uint32_t n = F_CPU / 1000;
		uint8_t clksel = 1;

		//odredjivanje vrednosti preskalera i periode tajmer brojac modula
		while(n > 255)
		{
			n /= 8;
			clksel++;
		}

		//tajmer/brojac modul 0: podesavanje preskalera
		TCCR0B = clksel;
		// tajmer/brojac modul 0: podesavanje periode
		OCR0A = (uint8_t)(n & 0xff) - 1;
		//tajmer/brojac modul 0 : dozvola prekida
		TIMSK0 = 0x02;
		//globalna dozvola prekida
		sei();
	}


/**
 * Funkcija koja proverava da li je protekla jedna sekunda od trenutka t0.
 * Trenutak to je izrazen u broju milisekundi proteklih od pokretanja tajmera 0.
 * @param- t0-Trenutak
 * return - Vrednost 1,ukoliko jeste,odnosno vrednost 0 ukoliko nije.
 */



///Deklarisanje promeljvie ms koja se vec nalazi u timer.c fajlu
extern volatile unsigned long ms;





/**
 * Funkcija koja proverava da li je protekla jedna sekunda od trenutka t0.
 * Trenutak to je izrazen u broju milisekundi proteklih od pokretanja tajmera 0.
 * @param- t0-Trenutak
 * @return - Vrednost 1,ukoliko jeste,odnosno vrednost 0 ukoliko nije.
 */

uint8_t secPass(uint32_t t0)
{
timer0Init();
uint32_t proteklo_vreme = ms;
if ((proteklo_vreme - t0) >= 1000)
{
return 1;
}
else
{
return 0;
}

}





int main()
{
usartInit(9600);
pinInit(PORT_B,DIODE_PIN,OUTPUT);
timer0Init();








return 0;
}














