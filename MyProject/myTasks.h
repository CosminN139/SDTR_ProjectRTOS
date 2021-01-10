/*
 * myTasks.h
 *
 * Created: 10/20/20
 *  Author: Cosmin Nastase
 */ 


#ifndef MYTASKS_H_
#define MYTASKS_H_

//let's define some task priorities
#define LED_TASK_PRIORITY						(tskIDLE_PRIORITY)
#define LCD_TASK_PRIORITY						(tskIDLE_PRIORITY)
#define mainButton_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )
#define SENSOR_TASK_PRIORITY					(tskIDLE_PRIORITY + 3)
#define SERIAL_TASK_PRIORITY					(tskIDLE_PRIORITY + 4)

TaskHandle_t myTaskHandle;
TaskHandle_t mySensorTaskHandle;

extern xSemaphoreHandle xButtonSemaphore;
extern xSemaphoreHandle xSensorSemaphor;
extern xSemaphoreHandle xSerialSemaphore;
extern uint16_t temperature;
extern uint16_t humidity;

//let's prototype some functions
void vFlashLEDTask1	(void *pvParameters);
void vFlashLEDTask2	(void *pvParameters);
void vIntTask		(void *pvParameters);
void vLCDUpdateTask  (void *pvParameters);
void vButtonCheckTask( void *pvParameters );
void vSensorCheck   (void *pvParameters);


#endif /* MYTASKS_H_ */