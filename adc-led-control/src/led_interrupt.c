/*
 * Lab 6.c
 *
 * Created: 6/24/2025 11:48:43 AM
 * Author : lukaf
 */ 

#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>

#define ROWS 4
#define COLS 4

volatile uint8_t entry = 0;		// Create global volatile variable to be accessed, but not optimized

const uint8_t keyPad[ROWS][COLS] = {
	{1, 2, 3, 0},
	{4, 5, 6, 0},
	{7, 8, 9, 0},
	{0, 0, 0, 0}
};

void keyPad_init()
{
	// Using PD4 - PD& as output (rows)
	DDRD |= 0b11110000;		// Set as output
	PORTD |= 0b11110000;	// Set rows high initially
	
	// PB0 - PB3 as input with pull-up (columns)
	DDRB &= ~(0b00001111);	// Set as input
	PORTB |= 0b00001111;	// Set pull-up
}

void timer0_init()
{	
	TCCR0A |= (1 << WGM01);		// Set CTC Mode
	TCCR0B |= (1 << CS02) | (1 << CS00);	// Pre-scaler 1024
	
	OCR0A = 62;		// Derived using lecture calculations
		
	TIMSK0 |= (1 << OCIE0A);	// Enable the specific interrupt
}

void timer2_init()
{
	TCCR2A |= (1 << WGM21);		// Set CTC Mode
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);	// Pre-scaler 1024
	
	OCR2A = 30;		// Good for 4ms interval with 500Hz
	
	TIMSK2 |= (1 << OCIE2A) | (1 << OCIE2B);	// Enable the specific interrupt
}

int main(void)
{
	DDRB |= (1 << 5);		// Set LED as output
	
	// Call initialization functions
	keyPad_init();
	timer0_init();
	timer2_init();
	
	sei();					// Enable global interrupts
		
    while (1) 
    {}												// Keep infinite while loop

}
// ISR Functions
ISR(TIMER0_COMPA_vect)
{
	for (uint8_t i = 0; i < ROWS; i++)
	{
		PORTD |= 0b11110000;		// Set all rows to LOGIC HIGH
		PORTD &= ~(1 << (i + 4));	// Set current row to LOGIC LOW
			
		for (uint8_t j = 0; j < COLS; j++)
		{
			if (!(PINB & (1 << j)))		// Check if button was pressed at [i][j]
			{
				entry = keyPad[i][j]; // Save keypad number pressed as global variable
			}
		}
	}
}

ISR(TIMER2_COMPA_vect)
{
	PORTB |= (1 << 5);		// Turn LED ON
	OCR2B = (OCR2A / 10) * entry;		// Set duty cycle %
}

ISR(TIMER2_COMPB_vect)
{
	PORTB &= ~(1 << 5);		// Turn LED OFF
}