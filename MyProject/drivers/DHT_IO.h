/*
 * DHT_IO.h
 *
 * Created: 12/08/20 3:01:03 PM
 *  Author: cnast
 */ 


#ifndef DHT_IO_H_
#define DHT_IO_H_


//Definitions
#define Input		0
#define Output		(!Input)
#define Low			0
#define High		(!Low)
#define False		0
#define True		(!False)

int BitCheck		(uint8_t x , uint8_t y);
void BitSet			(uint8_t x , uint8_t y);
void DigitalWrite	(uint8_t pin , uint8_t state);
void PinMode		(uint8_t pin , uint8_t state);
int	 DigitalRead	(uint8_t pin);



#endif /* DHT_IO_H_ */