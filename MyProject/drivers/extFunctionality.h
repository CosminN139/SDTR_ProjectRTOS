/*
 * extFunctionality.h
 *
 * Created: 10/20/20 6:37:35 PM
 *  Author: cnast
 */ 


#ifndef EXTFUNCTIONALITY_H_
#define EXTFUNCTIONALITY_H_

//////////////////////////////////////////////////////////////////////////
/*Port definig stuff for new functionality*/
#define PORT_INText		PORTE
#define DDR_INText		DDRE
#define BIT_INText		7

#define PORT_SWITCH_IP  PORTB
#define DDR_SWITCH_IP   DDRB
#define PIN_SWITCH_IP   PINB
#define BIT_SWITCH_IP   7

#define PORT_SWITCHSERIAL_IP  PORTB
#define DDR_SWITCHSERIAL_IP   DDRB
#define PIN_SWITCHSERIAL_IP   PINB
#define BIT_SWITCHSERIAL_IP   6

void vButtonInit(void);
void vButtonSerialInit(void);
char xButtonGetStatus(void);
char xSensorGetStatus(void);
char xSerialGetStatus(void);
//////////////////////////////////////////////////////////////////////////

void ext_int_init	(	void		);


#endif /* EXTFUNCTIONALITY_H_ */