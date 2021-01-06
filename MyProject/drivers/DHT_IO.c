/*+     */
/************************************************************************/

#include <inttypes.h>
#include <avr/io.h>

#include "DHT_IO.h"

//Defining some prototypes to hack already written code from AVR-DHT library
//Hardcoded DHT dedicated port to test the usage 

int BitCheck (uint8_t x , uint8_t y)
{
	if ( x & (1UL << y)) return True;
	else return False;
	
	
}
void BitSet (uint8_t x , uint8_t y)

{
	x |=	(1UL	<<	y);
}

void DigitalWrite (uint8_t pin , uint8_t state)
{
	if (state == Low) 
		{
			PORTC &= ~pin;
		} 
		else 
		{
			PORTC |= pin;
		}	
}

void PinMode (uint8_t pin , uint8_t state)
{
	if (state == Input) 
		{
			DDRC  &= ~pin;
			PORTC &= ~pin;
		
		}
		 else 
		{
			DDRC |= pin;	
		}
	
}

int DigitalRead	(uint8_t pin)
{	

	if (PORTC & pin) return High;
		return Low;

}