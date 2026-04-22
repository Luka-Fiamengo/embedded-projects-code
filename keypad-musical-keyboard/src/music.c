/*
 * Lab 5.c
 *
 * Created: 6/17/2025 8:28:06 AM
 * Author : lukaf
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#define ROWS 4
#define COLS 4

// 4x4 keypad mapped to tone indices
const uint8_t keypadToneIndex[ROWS][COLS] = {
	{0, 1, 2, 3},		// 1, 2, 3, A
	{4, 5, 6, 7},		// 4, 5, 6, B
	{8, 9, 10, 11},		// 7, 8, 9, C
	{12, 13, 14, 15}	// *, 0, #, D
};

// Keypad initialization (and speaker)
void Keypad_init()
{
	// Using PD4 - PD7 as output (rows)
	DDRD |= 0b11110000;		// Set as output
	PORTD |= 0b11110000;	// Set rows high initially
	
	// PB0 - PB3 as input with pull-up (columns)
	DDRB &= ~(0b00001111);	// Set as input
	PORTB |= 0b00001111;	// Set pull-up
	
	DDRD |= (1 << 1);		// Set pin 1 of Port D as data output for speaker
}

uint8_t keypadNote(int x)
{
	double freq = 440 * pow(2.0, (x - 9) / 12.0);		// Frequency calculation
	double ocr_val = (F_CPU / (2.0 * 256.0 * freq)) - 1.0;	// Convert frequency to ticks (CTC)
	
	if (ocr_val > 255)
		ocr_val = 255;		// Set the value to an 8-bit range
	else if (ocr_val < 0)
		ocr_val = 0;
	
	return (uint8_t)ocr_val;				// Return the OCR0A value
}

// Play tone cycle on PD1
void playTone(uint8_t ocr_val)
{
	TCCR0A |= (1 << WGM01);			// Set Timer Mode to CTC
	TCCR0B |= (1 << CS02);			// Pres-scaler 256
	OCR0A = ocr_val;				// Load compare value for frequency
	
	// Toggle PD1 manually
	PORTD |= (1 << 1);				// Speaker ON
	while(!(TIFR0 & (1 << OCF0A)));		// Busy-while to wait for overflow event
	TIFR0 |= (1 << OCF0A);		// Reset the overflow flag (write Logic 1 to it)
	
	
	PORTD &= ~(1 << 1);				// Speaker OFF
	while(!(TIFR0 & (1 << OCF0A)));		// Busy-while to wait for overflow event
	TIFR0 |= (1 << OCF0A);		// Reset the overflow flag
}

// Main Loop - Tone generator
void toneGenerator()
{
	while(1)
	{
		for (uint8_t i = 0; i < ROWS; i++) 
		{
			PORTD |= 0b11110000;		// Set all rows to HIGH
			PORTD &= ~(1 << (i + 4));		// Set current row to LOW
			
			for (uint8_t j = 0; j < COLS; j++)
			{
				if (!(PINB & (1 << j)))				// Check if button at [i][j]
				{
					while (!(PINB & (1 << j)));		// Wait for release
					
					uint8_t x = keypadToneIndex[i][j];	// Get tone index
					uint8_t ocr_val = keypadNote(x);	// Calculate OCR0A value
					
					for (int k = 0; k < 300; k++)		// Generate short tone
					{
						playTone(ocr_val);
					}
				}
			}
			PORTD |= (1 << (i + 4));		// Restore row to HIGH
		}
	}
}

int main(void)
{
    Keypad_init();
	toneGenerator();
}