/*
 * Lab 3.c
 *
 * Created: 6/10/2025 7:27:56 AM
 * Author : lukaf
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#define BAUDRATE ((F_CPU) / (BAUD * 16UL) - 1)
#include <avr/io.h>
#include <util/delay.h>

#define ROWS 4
#define COLS 4

const char keypad[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

void USART_int(void)
{
	UBRR0H = 0;		// Clear the high bits to 0
	UBRR0L = BAUDRATE;	// Set the Baud Rate
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);	// Enable Receiver and Transmitter
	
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);		// 8 bit data frame (011) according to table
	UCSR0C &= ~(1 << USBS0);			// Set USBSn = 0 for stop bit (1)
}

void USART_transmit(unsigned char data)
{
	while(!(UCSR0A & 1 << UDRE0)); // Do nothing until the buffer is empty
	UDR0 = data;
}	

// Keypad initialization
void Keypad_init()
{
	// Using PD4 - PD7 as output (rows)
	DDRD |= 0b11110000;		// Set as output
	PORTD |= 0b00001111;	// Set rows high initially
	
	// PB0 - PB3 as input with pull-up (columns)
	DDRB &= ~(0b00001111);	// Set as input
	PORTB |= 0b00001111;	// Set pull-up
}

// Scan the keyboard and return the ASCII character if pressed
void Scan_keypad() 
{
	for (int i = 0; i < ROWS; i++)			// Scan through all ROWS
	{
		PORTD |= 0b11110000;			// Set all rows HIGH
		PORTD &= ~(1 << (i + 4));		// Set current row to LOW
				
		for (int j = 0; j < COLS; j++)		// Scan through all COLS
		{
			if (!(PINB & (1 << j)))			// If column pin reads low
			{
				_delay_ms(100);					// De-bounce
				while (!(PINB & (1 << j)));			// Busy while
				USART_transmit(keypad[i][j]);		// The button at position [row][col] was pressed
			}
		}
		PORTD |= (1 << (i + ROWS));			// Return the specific row to LOGIC HIGH
	}
}


int main(void)
{
	USART_int();			// Initialize the USART
	Keypad_init();			// Initialize the proper keypad logic
	
    while (1) 
    {
		Scan_keypad();		// Call the iterative function to see what button was pressed
    }
}
