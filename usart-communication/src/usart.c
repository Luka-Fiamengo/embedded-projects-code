/*
 * Lab 2.c
 *
 * Created: 6/6/2025 8:24:34 AM
 * Author : lukaf
 */ 


#define F_CPU 16000000UL
#define BAUD 9600		// Define BAUD
#define BAUDRATE ((F_CPU) / (BAUD * 16UL) - 1)	// Set the Baud rate based on computer clock cycle and provided formula
#include <avr/io.h>
#include <util/delay.h>

// function to initialize the USART, set baud 
void USART_init(void)
{
	UBRR0H = 0;		// Clear the high bits to 0
	UBRR0L = BAUDRATE;	// Set the Baud Rate
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);	// Enable Receiver and Transmitter
	
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);		// 8 bit data frame (011) according to table
	UCSR0C &= ~(1 << USBS0);			// Set USBSn = 0 for stop bit (1)
}

// Transmit function
void USART_transmit(unsigned char data)
{
	while (!(UCSR0A & 1 << UDRE0));	// Do nothing until the buffer is empty
	UDR0 = data;
}


int main(void)
{
	USART_init();		// Initialize the USART
	char RED_ID[] = "130022344\r\n";
	
    while (1) 
    {
		// Transmit each character of the RED ID
		for (int i = 0; RED_ID[i] != '\0'; i++)
		{
			USART_transmit(RED_ID[i]);
		}
		
		_delay_ms(500);				// Delay 500ms


    }
}