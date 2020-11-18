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

Second , i started to mess with different delay functions to see which is best to use in our system

Third, i added an external interrupt to the system

Fourth , an LCD appeared in the scene
Made an reliable driver for it , transmits 8bit data format and configuration signals to mess with
every part of HD44870 controller features
*/
//////////////////////////////////////////////////////////////////////////

//compiler-defined includes
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

//aditional system-defined includes
#include "FreeRTOS.h"
#include "task.h"

//user-defined includes
#include "myTasks.h"
#include "testLED.h"
#include "LCD_Driver.h"

//global variables

void vLCDUpdateTask( void *pvParameters )
{
	static const uint8_t welcomeln1[] PROGMEM="FreeRTOS DEMO";
	portTickType xLastWakeTime;
	const portTickType xFrequency = 500;
	xLastWakeTime=xTaskGetTickCount();
	unsigned portBASE_TYPE uxTasks;
	LCDinit();
	LCDclr();
	LCDcursorOFF();
	CopyStringtoLCD(welcomeln1, 0, 0);
	//LCDcursorOn();
	LCDcursorOnBlink();
	while(1)
	{
		//uxTasks=uxTaskGetNumberOfTasks();
		
		//works only up to 9 tasks
		//LCDsendChar(uxTasks+48);
		/*if (xButtonSemaphore != NULL)
		{
			LCDGotoXY(3,1);
			//poll
			if (xSemaphoreTake(xButtonSemaphore, (portTickType)0)==pdTRUE)
			{
				LCDsendChar('1');
			}
			else
			{
				LCDsendChar('0');
			}
		}*/
		//vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

void vFlashLEDTask1 (void *pvParameters)
{
	vLEDTestInit();
	
	/*Parameters used for first delay function*/
	const portTickType xFrequency = 1000 *	(	configTICK_RATE_HZ / 1000	);	
	portTickType	xLastWakeTimeLED1;	
	xLastWakeTimeLED1 = xTaskGetTickCount();
	
	
	while(1)
	{
		vLEDTestToggle1();
		/*experimenting with delays*/
		
		// the original one , first discovered with the example:
		
		vTaskDelayUntil(&xLastWakeTimeLED1 , xFrequency); // 1sec delay		
		
		
		//other implementation of delay , i found it much easier to implement	:	
		
		//vTaskDelay(1000 * (	configTICK_RATE_HZ / 1000	));
		
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
/*
*As a first conclusion , the second and third delay functions i messed around the software are a bit imprecise
*Why imprecise? Well because the CPU while ticking the interval put in that delay function starts another task
*If that task lasts longer or a bit less than the ticking in the delay the cpu halts that tick and execute the rest of instructions after that
*So then the delay, in my function, is set to 1sec , but in reality could be 950ms or 1010ms
*In a non-time critical application i can use the second or third delay functions
*!!!!!!But if it is a time-critical app then the first function is mandatory because it makes the delay at the time specified!!!!!
*The bad thing seen at the first delay function is the amount of variables that i need to use
*More variables means more memory used...and that's not a pretty good thing sometimes
*So for this usage we need a pretty good optimisation
*/

	//////////////////////////////////////////////////////////////////////////
	//let's add another task in the game

TaskHandle_t myTaskHandle	 = NULL;

void vFlashLEDTask2(void *pvParameters)
{
	vLEDTestInit();
		const portTickType xFrequency2 = 500 *	(	configTICK_RATE_HZ / 1000	);
		portTickType	xLastWakeTimeLED2;
		xLastWakeTimeLED2 = xTaskGetTickCount();
	
	while(1)
	{
		vLEDTestToggle2();
		//vTaskDelay (500 * (	configTICK_RATE_HZ / 1000	)); 
		//we'll use this ... another time yeah
		vTaskDelayUntil (&xLastWakeTimeLED2 , xFrequency2);
	}
}

//////////////////////////////////////////////////////////////////////////
/*
*Another conclusion , after i messed a bit with the functions that deals with the external interrups
*It is not so straightforward as i seen in the os manual,from the fact that for AVR chips doesn't have 
*a pretty good designated descriptor for interrupt handling without queues or oter task scheduling stuff
*But after a bit of search on some obsolete parts of google and some beers taken apart i found that function
*vPortYieldFromTick returns the stack pointer from the interrupt service routine in the main program 
*/
void vIntTask(void *pvParameters)
{	

	vLEDTestInit();
	while(1)
	{
		vTaskSuspend(myTaskHandle);
		vLEDIntToggle();
		
	}
}

