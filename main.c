#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "keypad.h"
#include "pin.h"
#include "timer0.h"
#include "usart.h"
#include "input_event.h"
#include "output_event.h"


/** Funkcija za rad sa prekidima
	 *
	 */
	void timer0Init()
	{
		//tajmer0 u CTC mood
		TCCR0A = 0x02;
		#if F_CPU > 20000000
		#error "Frekvencija takta mora biti manja od 20Mz"
		#endif

		//inicijalizacija promenljivih za preskaler i periodu
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
		//tajmer/brojac modul 0: podesavanje periode
		OCR0A = (uint8_t)(n & 0xff) - 1;
		//tajmer/brojac modul 0 : dozvola prekida
		TIMSK0 = 0x02;
		//globalna dozvola prekida
		sei();
	}

int main()
{

usartInit(9600);
pinInit(PORT_B, DIODE_PIN, OUTPUT);
timer0Init();
uint8_t c,s,m,x,t0;
uint8_t min(uint8_t a, uint8_t b)
{
    return (a < b) ? a : b;
}

typedef enum state_t {ON, OFF, MINUTES_INPUT, SECONDS_INPUT, RUN} state_t;
enum state_t state = ON;


while(1)
{

	switch (state)
	{
		case ON:

		while (usartAvailable() == 0) ;
		c = usartGetChar ();
		if (c == 'B')
		{
			ledOff();
			logTran(ON, OFF);
			state = OFF;
		}
		else if (c == 'C')
		{
			ledBlink();
			s = 0;
			logTran(ON, SECONDS_INPUT);
			state = SECONDS_INPUT;
		}
		else
		{
			ledBlink();
			m = 0;
			logTran(ON, MINUTES_INPUT);
			state = MINUTES_INPUT;
		}
		break;


		case MINUTES_INPUT:

				while (usartAvailable() == 0) ;
				c = usartGetChar ();
				if ('0' <= c && c <= '9' && m <= 99)
				{
					ledBlink();
					x = min(m*10+c, 99);
					logTime(m,s);
					state = MINUTES_INPUT;
				}
				else if (c == 'B')
				{
					ledOff();
					logTran(MINUTES_INPUT, OFF);
					state = OFF;
				}
				else
				{
					ledBlink();
					m = 0;
					logTran(MINUTES_INPUT, SECONDS_INPUT);
					state = SECONDS_INPUT;
				}

		break;





		case RUN:
			while (usartAvailable() == 0) ;
			c = usartGetChar ();
			if (secPass(t0) && s == 0)
			{
				ledBlink();
				m--;
				s = 59;
				logTime(m,s);
				state = RUN;
			}

		break;
	}


}












return 0;

}
