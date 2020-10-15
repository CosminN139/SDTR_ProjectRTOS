/*
 * A little start in RTOS projects
 *
 * Created: 10/15/20 
 * Author : Cosmin Nastase
 */ 

/*			*****Description*****
* The purpose of the project is to demostrate the utility of a RTOS system on a microcontroller-based app
* For this project im going to use an Waveshare STK128+ ATMega128 - based development board 
*/


/*
			*****First prototype*****
* In this part of the project i am going to blink a led at one second interval, pretty much basic stuff 
* yet fundamental for testing the good functioning of the system on uC 
*/

#include <avr/io.h>

#include "FreeRTOS.h"
#include "task.h"


//let's define some ports for our little led to glow on rtos
#define PORT_LED	PORTB
#define DDR_LED		DDRB
#define BIT_LED		2

//let's define some task priorities
#define LED_TASK_PRIORITY	(tskIDLE_PRIORITY)


//*******************************************************************************************************************************************

//now let's prototype a function to initialize the output

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

//now let's prototype a task for toggling the led

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

portSHORT main(void)
{
   xTaskCreate(vFlashLEDTask, (const char *) "LED" , configMINIMAL_STACK_SIZE , NULL , LED_TASK_PRIORITY , NULL);
   
   vTaskStartScheduler();
   
    while (1) 
    {
    }
	return 0;
}

