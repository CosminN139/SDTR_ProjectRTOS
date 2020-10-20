/*
 * myTasks.h
 *
 * Created: 10/20/20
 *  Author: Cosmin Nastase
 */ 


#ifndef MYTASKS_H_
#define MYTASKS_H_

//let's define some task priorities
#define LED_TASK_PRIORITY	(tskIDLE_PRIORITY)

TaskHandle_t myTaskHandle;

//let's prototype some functions
void vFlashLEDTask1	(void *pvParameters);
void vFlashLEDTask2	(void *pvParameters);
void vIntTask		(void *pvParameters);

#endif /* MYTASKS_H_ */