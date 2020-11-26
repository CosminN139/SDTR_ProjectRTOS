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

			*****Third prototype -> done*****
*Messing with different delay implementations in the system , why are they good in some cases and why not in others
*Creating more tasks for the system -> more blinks for me , yey
			
			*****Fourth prototype -> done*****
*Complicated my life ,again, with interrupts...let's see what is going to happen here
*Update,after half of day of hardcore research and some beers, it finally works, been there done that :)

		    *****Fifth prototype*****
*After struggling a bit with the interrupts and stuff like that, it is the time to add some peripherals to our board
*So in this update we'll have a pretty much functional LCD driver with some tasks to treat with our already functional example.
*After some long sessions is finnaly alive!!!!!

*TO DO: A little bit of messing with the memory locations of each point on LCD and reach a better timing for each function//

Added a little feature...a button without interrupts. Its main task is to print something on LCD.
*made some hou
*/



//compiler-defined includes
#include <avr/io.h>

//aditional system-defined includes
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//user-defined includes
#include "myTasks.h"
#include "demos/testLED.h"
#include "drivers/extFunctionality.h"
#include "drivers/LCD_Driver.h"


//global variables,magic numbers etc.
xSemaphoreHandle xButtonSemaphore=NULL;

//////////////////////////////////////////////////////////////////////////

portSHORT main(void)
{		
	ext_int_init();
	
	vSemaphoreCreateBinary(xButtonSemaphore);
	if(xButtonSemaphore!=NULL)
	{
		//successfully created
		xTaskCreate( vButtonCheckTask, (const char* ) "Button", configMINIMAL_STACK_SIZE, NULL, mainButton_TASK_PRIORITY, NULL );
	}
	
   xTaskCreate(vFlashLEDTask1, (const char *) "LED" , configMINIMAL_STACK_SIZE , NULL , LED_TASK_PRIORITY , NULL);
   xTaskCreate(vFlashLEDTask2, (const char *) "LED" , configMINIMAL_STACK_SIZE , NULL , LED_TASK_PRIORITY , NULL);
   xTaskCreate(vIntTask	     , (const char *) "interrupt" , configMINIMAL_STACK_SIZE , NULL , LED_TASK_PRIORITY , &myTaskHandle);
   xTaskCreate(vLCDUpdateTask , (const char *) "LCD start routine" , configMINIMAL_STACK_SIZE , NULL , LCD_TASK_PRIORITY , NULL);
   
   vTaskStartScheduler();
   
   //the system should not reach this
    while (1) 
    {
    }
	return 0;
}

