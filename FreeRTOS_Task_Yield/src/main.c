/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
//Dscription- This program demonstrate how freetask yield api can be used to trigger
//context switching when task completes its functionality before tick timer expires.

#include "stm32f4xx.h"
#include"FreeRTOS.h"
#include"task.h"
#include<stdint.h>
#include<stdio.h>

//function prototype
void vTask(void * pvParams);

//Task handler or task ID
TaskHandle_t xTask1Handle = NULL;
TaskHandle_t xTask2Handle = NULL;


int main(void)
{
	RCC_DeInit();

	SystemCoreClockUpdate();

	const int task_1_param = 1;
	const int task_2_param = 2;

	xTaskCreate(vTask, "Task-1", configMINIMAL_STACK_SIZE, (void *)&task_1_param, 1, &xTask1Handle);
	xTaskCreate(vTask, "Task-2", configMINIMAL_STACK_SIZE, (void *)&task_2_param, 1, &xTask2Handle);

	vTaskStartScheduler();


	for(;;);
}

void vTask(void * pvParams)
{
	//volatile unsigned int i = 0;
	const int * tParam = (const int *)pvParams;
	while(1)
	{
		/*
		 * Do what This task is meant to do
		 */
		printf("Task-%d Running\r\n", *tParam);


		/*
		 * Now assumes that task has completed its function,
		 * so let's yield this task so that other tasks are
		 * waiting to be scheduled are allowed to run.
		 */
		printf("Task-%d Complete - Yielding Task...\r\n\n\n", *tParam);
		taskYIELD();
	}
}
