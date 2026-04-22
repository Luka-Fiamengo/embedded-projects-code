/*
 * Extra Credit Lab.c
 *
 * Created: 7/2/2025 6:56:31 PM
 * Author : lukaf
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#define BAUDRATE ((F_CPU) / (BAUD * 16UL) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>

volatile char RED_ID[] = "130022344\r\n";
volatile uint8_t i = 0;		// Track the current character in the ISR, used as the index that was original code in main

// function to initialize the USART, set baud
void USART_init(void)
{
	UBRR0H = 0;		// Clear the high bits to 0
	UBRR0L = BAUDRATE;	// Set the Baud Rate
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << UDRIE0);	// Enable Receiver and Transmitter, plus Interrupt
	
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);		// 8 bit data frame (011) according to table
	UCSR0C &= ~(1 << USBS0);			// Set USBSn = 0 for stop bit (1)
}

// Utilized as our original _delay_ms(500) from original code
void timer1_init()
{
	TCCR1B |= (1 << WGM12) | (1 << CS12);		// Enable CTC Mode, Pre-scaler 256
		
	OCR1A = 31249;		// Calculated OCR0A value --> X = (65536 * 500 ms) / 1048.576 ms
	
	TIMSK1 |= (1 << OCIE1A);		// Enable specific Timer1 Interrupt
}

int main(void)
{
	USART_init();
	sei();				// Enable global interrupts
	
    while (1) 
    {
		// Keep infinite while loop empty when using ISRs
    }
}

// ISR for USART Data Register Empty
ISR(USART_UDRE_vect)
{
	// Change initial for loop from Lab 2 to if-else in ISR
	if (RED_ID[i] != '\0')
	{
		UDR0 = RED_ID[i++];
	} else {
		i = 0;
		UCSR0B &= ~(1 << UDRIE0);		// Disable interrupt once finished
		timer1_init();			// Call this function as our 'delay'
	}	
	
	
}

ISR(TIMER1_COMPA_vect)
{
	TIMSK1 &= ~(1 << OCIE1A);		// Disable the Timer1 Interrupt
	
	TCCR1B = 0;		// Setting to zero, stops the timer by resetting Pre-scale
	
	UCSR0B |= (1 << UDRIE0);		// Re-enable the USART transmission
}