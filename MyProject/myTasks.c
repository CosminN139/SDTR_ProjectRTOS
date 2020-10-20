/*
 * myTasks.c
 *
 * Created: 10/20/20
 *  Author: Cosmin Nastase
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

void vFlashLEDTask1 (void *pvParameters)
{
	vLEDTestInit();
	
	/*Parameters used for first delay function
	
	portTickType	xLastWakeTime;
	const portTickType xFrequency = 1000;
	xLastWakeTime = xTaskGetTickCount();
	*/
	
	while(1)
	{
		vLEDTestToggle1();
		/*experimenting with delays*/
		
		// the original one , first discovered with the example:
		/*
		vTaskDelayUntil(&xLastWakeTime , xFrequency); // 1sec delay		
		*/
		
		//other implementation of delay , i found it much easier to implement	:	
		
		vTaskDelay(1000 * (	configTICK_RATE_HZ / 1000	));
		
		//pretty much the same , but in this case the formula is ** (number of ticks * ( freqency of ticks / 1000)) **
		//in our case because we defined in conf file the tick rate at 1000 the delay will be at exactly 1 sec everytime
		
		//the last one i found searching stuff about delays , but is the cheeckiest one yet
		/*
		vTaskDelay(pdMS_TO_TICKS (1000)	);
		*/
		//it pretty much makes the same thing like the formula described in the other delay function call
		//in the prototype of the function we'll see the formula like:
		/*	DO NOT UNCOMMENT THIS EVER EVER
		pdMS_TO_TICKS( xTimeInMs )    ( ( TickType_t ) ( ( ( TickType_t ) ( xTimeInMs ) * ( TickType_t ) configTICK_RATE_HZ ) / ( TickType_t ) 1000U ) )
		*/
		//that is like i did the writing in the other delay
		//but ... yeah , i didn't put every parameter type like in that description
		
	}

}
	//////////////////////////////////////////////////////////////////////////
	//let's add another task in the game


void vFlashLEDTask2(void *pvParameters)
{
	vLEDTestInit();
	
	while(1)
	{
		vLEDTestToggle2();
		vTaskDelay (500 * (	configTICK_RATE_HZ / 1000	));
	}
}


