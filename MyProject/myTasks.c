/*
 * myTasks.c
 *
 * Created: 10/20/20 3:20:17 PM
 *  Author: cnast
 */ 


//////////////////////////////////////////////////////////////////////////
/*
				Short description
				
In this file we'll be defining tasks for our system

First , i'm gona make the led blinking work again also in this structure 
*/
//////////////////////////////////////////////////////////////////////////

//compiler-defined includes

//aditional system-defined includes
#include "FreeRTOS.h"
#include "task.h"

//user-defined includes
#include "myTasks.h"
#include "testLED.h"

void vFlashLEDTask (void *pvParameters)
{
	vLEDTestInit();
	portTickType	xLastWakeTime;
	const portTickType xFrequency = 1000;
	xLastWakeTime = xTaskGetTickCount();
	for( ;; )
	{
		vLEDTestToggle();
		vTaskDelayUntil(&xLastWakeTime , xFrequency);
	}
}
