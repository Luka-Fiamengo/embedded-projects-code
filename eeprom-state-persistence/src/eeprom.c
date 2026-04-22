/*
 * Lab 8.c
 *
 * Created: 7/1/2025 9:51:38 AM
 * Author : lukaf
 */ 

#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

uint8_t EEMEM location_duty = 0;		// EEPROM variable used to store the duty cycle

void timer0_init()
{
	TCCR0A |= (1 << WGM01);			// Enable CTC Mode
	TCCR0B |= (1 << CS00) | (1 << CS02);		// Set pre-scaler to 1024
	
	OCR0A = 77;			// Calculated value that works for 5ms period
	OCR0B = 0;			// Duty Cycle starts at 0
	
	TIMSK0 |= (1 << OCIE0A) | (1 << OCIE0B);		// Enable the specific COMPA and COMPB interrupts
}



int main(void)
{
	uint8_t duty_percent;			// Holds the current duty cycle to be used (0 to 100)
	
	DDRB |= (1 << PORTB5);			// Set PB5 (LED) as output
	
	timer0_init();
		
	duty_percent = eeprom_read_byte(&location_duty);	// Read the last saved brightness from EEPROM and store in variable
	
	// Check if EEPROM has been initialized, is within bounds, and increments by 10
	if (duty_percent == 0xFF || duty_percent > 100 || duty_percent % 10 != 0) {
		duty_percent = 0;
	}
	else if (duty_percent == 100) {
		duty_percent = 0;		// Once it reaches 100, the brightness should be set back to zero 
	}
	else {
		duty_percent += 10;		// Increment the brightness of the LED by 10%
	}
	
	eeprom_update_byte(&location_duty, duty_percent);	// Write the updated value to EEPROM
	
	OCR0B = OCR0A * (duty_percent / 100.0);		// Calculate the OCRB (on time) for the PWM
	
	sei();			// Enable all global interrupts
	
    while (1) // Empty infinite while when using interrupts
    {
    }
}

ISR(TIMER0_COMPA_vect)
{
	PORTB |= (1 << PORTB5);			// Turn the LED ON 
}

ISR(TIMER0_COMPB_vect)
{
	PORTB &= ~(1 << PORTB5);		// Turn the LED OFF
}