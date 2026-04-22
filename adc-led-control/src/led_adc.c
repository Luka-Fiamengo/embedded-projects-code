/*
 * Lab 7.c
 *
 * Created: 6/27/2025 11:41:53 AM
 * Author : lukaf
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t ad_value = 0;		// Global variable to hold the Analog to Digital Conversion value
float timer2_duty = 0.0;

void adc_init()
{
	DDRC &= ~(1 << PINC4);			// Set PINC4 as an input
	ADMUX |= (1 << REFS0);			// Set Vcc as the reference voltage
	ADMUX |= (1 << MUX2);			// Select ADC4 as Analog Channel Selection
	
	// Enable ADC Auto Trigger and Conversion Complete Interrupt
	// Set Pre-Scaler to 128
	ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	ADCSRB |= (1 << ADTS1) | (1 << ADTS0);		// Compare match
}

void adc_return(uint8_t ch)
{
	ch &= 0b00000111;			// AND operation with 7 (error check mechanism)
	ADMUX = (ADMUX & 0xF8) | ch;	// Clear any previous settings
	
	ADCSRA |= (1 << ADSC);		// Start the conversion
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
	
	OCR2A = 255;		// Good for 4ms interval with 500Hz
	OCR2B = OCR2A * timer2_duty;
	
	TIMSK2 |= (1 << OCIE2A) | (1 << OCIE2B);	// Enable the specific interrupt
}

int main(void)
{
	DDRB |= (1 << PORTB5);			// Set LED as output
	
	// Call initialization functions
	adc_init();
	timer0_init();
	timer2_init();
	// adc_return(4);
	
	sei();					// Enable global interrupts
	
    while (1) 
    {
    }
}


// Interrupt for when OCR2A compare match occurs
ISR(TIMER2_COMPA_vect)
{
	if (timer2_duty > 0)
		PORTB |= (1 << PORTB5);			// Turn on LED if greater than 0
	else
		PORTB &= ~(1 << PORTB5);
}

// Interrupt for when OCR2B compare match occurs
ISR(TIMER2_COMPB_vect)
{
	PORTB &= ~(1 << PORTB5);			// Turn OFF LED
}

// Interrupt when ADC conversion is complete
ISR(ADC_vect)
{
	ad_value = ADC;						// Store results into global variable
	timer2_duty = (ad_value / 1023.0);	// Set results into percentage for LED duty cycle %
	
	if (timer2_duty >= 0.99)			// Cap at 99%
		timer2_duty = 0.99;
	OCR2B = OCR2A * timer2_duty;		// Update duty cycle
}