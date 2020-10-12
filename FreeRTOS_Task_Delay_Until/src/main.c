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
#include"FreeRTOS.h"
#include"task.h"
#include<stdint.h>
#include<stdio.h>

void vTask(void * pvParams);

int counter = 0;

int main(void)
{
	RCC_DeInit();

	SystemCoreClockUpdate();

	xTaskCreate(vTask, "T1", 150, NULL, 1, NULL);

	vTaskStartScheduler();

	for(;;);
}

void vTask(void * pvParams)
{
	TickType_t xLastWakeTime;

		//1000 ms in terms of tick

		const TickType_t xFrequency = 1000/ portTICK_PERIOD_MS;

		/*
		 * stamp current time. It is only required once
		 * it will be updated automatically with every call to vTaskDelayUntil()API
		 */
		xLastWakeTime = xTaskGetTickCount();
		while(1)
		{
			printf("Seconds Count: %d\n", counter++);

			//create 1 sec delay
			vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}
