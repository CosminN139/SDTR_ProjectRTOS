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
			*****First prototype -> done*****
* In this part of the project i am going to blink a led at one second interval, pretty much basic stuff 
* yet fundamental for testing the good functioning of the system on uC 

			*****Second prototype -> done*****
*In this part of the project i am going to separate all the functions and tasks of the system in distinct files
*for easy interpreting of the code

			*****Third prototype *****
*Messing with different delay implementations in the system , why are they good in some cases and why not in others
*Creating more tasks for the system -> more blinks for me , yey
*/

//compiler-defined includes
#include <avr/io.h>

//aditional system-defined includes
#include "FreeRTOS.h"
#include "task.h"

//user-defined includes
#include "myTasks.h"
#include "testLED.h"


//////////////////////////////////////////////////////////////////////////

portSHORT main(void)
{
   xTaskCreate(vFlashLEDTask1, (const char *) "LED" , configMINIMAL_STACK_SIZE , NULL , LED_TASK_PRIORITY , NULL);
   xTaskCreate(vFlashLEDTask2, (const char *) "LED" , configMINIMAL_STACK_SIZE , NULL , LED_TASK_PRIORITY , NULL);
   
   vTaskStartScheduler();
   
   //the system should not reach this
    while (1) 
    {
    }
	return 0;
}

