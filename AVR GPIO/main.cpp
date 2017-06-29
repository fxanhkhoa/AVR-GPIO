/*
 * AVR GPIO.cpp
 *
 * Created: 6/22/2017 5:05:36 PM
 * Author : Anh Khoa
 */ 

#include <avr/io.h>
#define  F_CPU 8000000
#include <util/delay.h>

/****** PROTOTYPE ******/
void Mode1();
void Mode2();

int main(void)
{
	int mode = 1;
    /* Replace with your application code */
	DDRA = 0xFF; // Set Output for PORTA
	DDRB = 0x00; // Set Input for PORTB
	DDRC = 0xFF; // Set Output for PORTC

	PORTA = 0xFF; // Set 5v output for all pin
	PORTB = 0xFF; // Internal pull up high for all pin
	PORTC = 0x00; // Set 0v output for all pin

    while (1) 
    {
		//PORTA ^= 0xFF; // Reverse bit (0 -> 1 and 1 -> 0)
		//_delay_ms(500); // Delay 100ms (base on Clock set)
		// find out if pin 0 or pin 4 of PORTB got low input signal
		if (((PINB & (1 << 0)) == 0) || (((PINB & (1 << 4)) == 0)))
		{
			PORTC = 0xFF;
			mode = 2;
			//if (mode == 3) mode = 1;
		}
		else 
		{
			PORTC = 0x00;
			mode = 1;
		}
		
		if (mode == 1) Mode1();
		else if (mode == 2) Mode2();
    }
}

void Mode1()
{
	PORTA = 0x00;
	_delay_ms(300);
	for (int i = 0;i < 8; i++)
	{
		PORTA |= (1 << i);
		_delay_ms(300);
	}
	PORTA = 0x00;
	_delay_ms(300);
	for (int i = 7; i >= 0; i--)
	{
		PORTA |= (1 << i);
		_delay_ms(300);
	}
}

void Mode2()
{
	PORTA = 0x00;
	_delay_ms(300);
	for (int i = 3; i >= 0 ; i--)
	{
		PORTA |= (1 << i) | (1 << (7-i));
		_delay_ms(300);
	}
	PORTA = 0x00;
	_delay_ms(300);
	for (int i = 0; i < 4; i++)
	{
		PORTA |= (1 << i) | (1 << (7-i));
		_delay_ms(300);
	}
}

