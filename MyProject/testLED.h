/*
 * testLED.h
 *
 * Created: 10/20/20 
 *  Author: Cosmin Nastase
 */ 



#ifndef TESTLED_H_
#define TESTLED_H_

//////////////////////////////////////////////////////////////////////////
/* Port defining for our little leds*/
#define PORT_LED1		PORTB
#define DDR_LED1		DDRB
#define BIT_LED1		1

#define PORT_LED2		PORTB
#define DDR_LED2		DDRB
#define BIT_LED2		2

#define PORT_LEDint		PORTB
#define DDR_LEDint		DDRB
#define BIT_LEDint		0
//////////////////////////////////////////////////////////////////////////


void vLEDTestInit		(void);
void vLEDTestToggle1	(void);
void vLEDTestToggle2	(void);
void vLEDIntToggle		(void);

#endif /* TESTLED_H_ */