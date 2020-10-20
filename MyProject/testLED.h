/*
 * testLED.h
 *
 * Created: 10/20/20 
 *  Author: Cosmin Nastase
 */ 



#ifndef TESTLED_H_
#define TESTLED_H_

#define PORT_LED	PORTB
#define DDR_LED		DDRB
#define BIT_LED		2

void vLEDTestInit	(void);
void vLEDTestToggle	(void);


#endif /* TESTLED_H_ */