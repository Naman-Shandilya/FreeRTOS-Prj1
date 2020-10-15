/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t mutexHandle;

void vTask1(void * pvParams);
void vTask2(void * pvParams);
			

int main(void)
{
	mutexHandle = xSemaphoreCreateMutex();

	if(mutexHandle != NULL)
	{
		xTaskCreate (vTask1, "T1", 200, NULL, 1, NULL);

		xTaskCreate (vTask2, "T2", 200, NULL, 1, NULL);
		vTaskStartScheduler();
	}
	for(;;);
}

void vTask1(void * pvParams)
{
	__IO uint i = 0;

	for(;;)
	{
		xSemaphoreTake(mutexHandle, portMAX_DELAY);

		printf("Message From Task-1: FreeRtos Task-1 Running...\n");

		xSemaphoreGive(mutexHandle);

		for(i = 0; i < 200000; i++);
	}
}

void vTask2(void * pvParams)
{
	__IO uint i = 0;

	for(;;)
	{
		xSemaphoreTake(mutexHandle, portMAX_DELAY);

		printf("Message From Task-2: FreeRTOS Task-2 Running....\n");

		xSemaphoreGive(mutexHandle);

		for(i=0; i < 200000; i++);
	}
}
