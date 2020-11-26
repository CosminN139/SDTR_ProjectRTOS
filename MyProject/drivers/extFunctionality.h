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

void vButtonInit(void);
char xButtonGetStatus(void);

//////////////////////////////////////////////////////////////////////////

void ext_int_init	(	void		);


#endif /* EXTFUNCTIONALITY_H_ */