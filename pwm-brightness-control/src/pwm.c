/*
 * Lab 4.c
 *
 * Created: 6/12/2025 10:49:46 AM
 * Author : lukaf
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void timer_init()
{
	TCCR0A |= (1 << WGM01);		// Set Timer Mode to CTC
	TCCR0B |= (1 << CS02) | (1 << CS00);		// Pre-scaler 1024
	
	OCR0A = 0x9B;		// Represents 10ms timer (155)
	OCR0B = 0x00;		// Initialize duty cycle 0%
}

void LED_init()
{
	DDRB |= (1 << 5);		// Set LED (PB5) as output
	DDRB &= ~(1 << 7);	// Button (PB7) as input
	PORTB |= (1 << 7);		// Pull-up enabled
}

// Wait until the timer reaches value in OCR0A
void compare_A()
{
	while(!(TIFR0 & (1 << OCF0A)));		// Busy-while to wait for overflow event
	TIFR0 |= (1 << OCF0A);		// Reset the overflow flag (write Logic 1 to it)
}

// Wait until the timer reaches value in OCR0B
void compare_B()
{
	while(!(TIFR0 & (1 << OCF0B)));		// Busy-while to wait for overflow event
	TIFR0 |= (1 << OCF0B);		// Reset the overflow flag
}

int main(void)
{
	LED_init();
	timer_init();
	
    while (1) 
    {
		// LED ON
		PORTB |= (1 << 5);		// PB5 to HIGH -> LED ON
		compare_B();			// Wait for duration of Ton (OCR0B)
						
		// LED OFF
		PORTB &= ~(1 << 5);		// PB5 to LOW -> LED OFF
		compare_A();			// Wait for duration of Toff (OCR0A)
		
		if (!(PINB & (1 << PORTB7)) && (OCR0B < OCR0A))
		{
			OCR0B++;
		}
		else if ((PINB & (1 << PORTB7)) && OCR0B > 0)
		{
			OCR0B--;
		}
    }
}