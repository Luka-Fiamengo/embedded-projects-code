/*
 * Lab 1.c
 *
 * Created: 6/2/2025 7:54:25 PM
 * Author : lukaf
 */ 

#define F_CPU 16000000UL  // 16MHz clock from the debug processor
#include <avr/io.h>
#include <util/delay.h>

// Functions for the dot, dash, and space

// Dot is represented by 1 unit or 200ms
void dot()
{
	PORTB |= (1 << PORTB5);		// Set port bit B5 to 1 to turn on LED
	_delay_ms(200);				// 1 unit is represented by 200ms 
	PORTB &= ~(1 << PORTB5);	// CLear port bit B5 to 0 to turn off LED
	_delay_ms(200);				// Off for 1 unit
}

// Dash is represented by 3 units or 600ms
void dash()
{
	PORTB |= (1 << PORTB5);
	_delay_ms(600);
	PORTB &= ~(1 << PORTB5);
	_delay_ms(200);				// Use 1 unit because the letters need seperation between their own parts
}

// Have to have two separate space functions, one for different letters and different words
// Space between letters is 3 units or 600ms
void spc_letter()
{
	PORTB &= ~(1 << PORTB5);
	_delay_ms(400);				// From the dot/dash transition we take the 600ms that represents a space and subtract 200ms
}

void spc_word()
{
	PORTB &= ~(1 << PORTB5);
	_delay_ms(1200);			// 1400 - 200 = 1200 ms
}

int main(void)
{
	DDRB |= (1 << DDB5);
	
	char NAME_ID[] = "Luka Fiamengo 130022344";
	int i = 0;
	
    while (1) 
    {
		if (NAME_ID[i] == '\0')
		{
			i = 0;			// Allows for an infinite run
		}
		// Letters
		else if (NAME_ID[i] == 'A' || NAME_ID[i] == 'a')
		{
			dot(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'B' || NAME_ID[i] == 'b')
		{
			dash(); dot(); dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'C' || NAME_ID[i] == 'c')
		{
			dash(); dot(); dash(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'D' || NAME_ID[i] == 'd')
		{
			dash(); dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'E' || NAME_ID[i] == 'e')
		{
			dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'F' || NAME_ID[i] == 'f')
		{
			dot(); dot(); dash(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'G' || NAME_ID[i] == 'g')
		{
			dash(); dash(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'H' || NAME_ID[i] == 'h')
		{
			dot(); dot(); dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'I' || NAME_ID[i] == 'i')
		{
			dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'J' || NAME_ID[i] == 'j')
		{
			dot(); dash(); dash(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'K' || NAME_ID[i] == 'k')
		{
			dash(); dot(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'L' || NAME_ID[i] == 'l')
		{
			dot(); dash(); dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'M' || NAME_ID[i] == 'm')
		{
			dash(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'N' || NAME_ID[i] == 'n')
		{
			dash(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'O' || NAME_ID[i] == 'o')
		{
			dash(); dash(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'P' || NAME_ID[i] == 'p')
		{
			dot(); dash(); dash(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'Q' || NAME_ID[i] == 'q')
		{
			dash(); dash(); dot(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'R' || NAME_ID[i] == 'r')
		{
			dot(); dash(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'S' || NAME_ID[i] == 's')
		{
			dot(); dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'T' || NAME_ID[i] == 't')
		{
			dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'U' || NAME_ID[i] == 'u')
		{
			dot(); dot(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'V' || NAME_ID[i] == 'v')
		{
			dot(); dot(); dot(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'W' || NAME_ID[i] == 'w')
		{
			dot(); dash(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'X' || NAME_ID[i] == 'x')
		{
			dash(); dot(); dot(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'Y' || NAME_ID[i] == 'y')
		{
			dash(); dot(); dash(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == 'Z' || NAME_ID[i] == 'z')
		{
			dash(); dash(); dot(); dot(); spc_letter();
			i++;
		}
		
		// Numbers
		else if (NAME_ID[i] == '0')
		{
			dash(); dash(); dash(); dash(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == '1')
		{
			dot(); dash(); dash(); dash(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == '2')
		{
			dot(); dot(); dash(); dash(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == '3')
		{
			dot(); dot(); dot(); dash(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == '4')
		{
			dot(); dot(); dot(); dot(); dash(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == '5')
		{
			dot(); dot(); dot(); dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == '6')
		{
			dash(); dot(); dot(); dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == '7')
		{
			dash(); dash(); dot(); dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == '8')
		{
			dash(); dash(); dash(); dot(); dot(); spc_letter();
			i++;
		}
		else if (NAME_ID[i] == '9')
		{
			dash(); dash(); dash(); dash(); dot(); spc_letter();
			i++;
		}
		
		// Space between words
		else if (NAME_ID[i] == ' ')
		{
			spc_word();
			i++;
		}
    }
}