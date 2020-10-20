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

//let's prototype some functions
void vFlashLEDTask	(void *pvParameters);



#endif /* MYTASKS_H_ */