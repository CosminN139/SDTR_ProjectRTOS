/*
 * extFunctionality.c
 *
 * Created: 10/20/20
 *  Author: Cosmin Nastase
 */ 

//compiler-defined includes
#include <avr/interrupt.h>

//aditional system-defined includes
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

//user-defined includes
#include "myTasks.h"
#include "testLED.h"
#include "extFunctionality.h"

//global variables,magic numbers etc.

//////////////////////////////////////////////////////////////////////////

/*
let's handle an external interrupt 
*/



ISR(INT7_vect)
{	
	vPortYieldFromTick();
	xTaskResumeFromISR(myTaskHandle);	
}

void ext_int_init	(	void	)
{
	DDR_INText	&=	~(	1 << BIT_INText		);
	PORT_INText	|=	 (	1 << BIT_INText		);
	EICRB		|=	 (	1 << ISC70			);
	EIMSK		|=	 (	1 << INT7			);
}