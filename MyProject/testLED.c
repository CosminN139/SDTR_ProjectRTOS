/*
 * testLED.c
 *
 * Created: 10/20/20 
 *  Author: Cosmin Nastase
 */ 

//////////////////////////////////////////////////////////////////////////
/*
				Short description
				
A test function used early to see if the RTOS is working

*/

//compiler-defined includes

//aditional system-defined includes
#include "FreeRTOS.h"
#include "task.h"

//user-defined includes
#include "testLED.h"

void vLEDTestInit(void)
{
	//set PORTB direction to output
	DDR_LED  |=	 (1	<< BIT_LED);
	PORT_LED &= ~(1	<< BIT_LED);
}


void vLEDTestToggle (void)
{
	vTaskSuspendAll();
	{
		PORT_LED ^= (1	<<	BIT_LED);
	}
	xTaskResumeAll();
}