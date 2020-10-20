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
	DDR_LED1  |=	 (1	<< BIT_LED1);
	PORT_LED1 &=	~(1	<< BIT_LED1);
	
	DDR_LED2  |=	 (1	<< BIT_LED2);
	PORT_LED2 &=	~(1	<< BIT_LED2);
}


void vLEDTestToggle1 (void)
{
	vTaskSuspendAll();
	{
		PORT_LED1 ^= (1	<<	BIT_LED1);
	}
	xTaskResumeAll();
}

void vLEDTestToggle2 (void)
{
	vTaskSuspendAll();
	{
		PORT_LED2 ^= (1	<<	BIT_LED2);
	}
	xTaskResumeAll();
}