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

//Task function handle prototype
void vTask(void * pvParams);

//Task handle or task id definition
TaskHandle_t xTask1Handle = NULL;
TaskHandle_t xTask2Handle = NULL;

int counter = 0;

int main(void)
{
	RCC_DeInit();

	SystemCoreClockUpdate();

	const int task_1_Num = 1;
	const int task_2_Num = 2;

	xTaskCreate(vTask, "Task-1", 150, (void*)&task_1_Num, 1, &xTask1Handle);
	xTaskCreate(vTask, "Task-2", 150, (void*)&task_2_Num, 1, &xTask2Handle);

	vTaskStartScheduler();

	for(;;);
}

void vTask(void * pvParams)
{
	volatile unsigned int i = 0;
	int *param = (int *)pvParams;
	while(1)
	{
		printf("Task-%d is Running \r\n", *param);
		counter++;
		if (counter == 10)
		{
			printf("Task-1 priority increases by 1");
			vTaskPrioritySet(xTask1Handle, uxTaskPriorityGet(xTask1Handle)+1);

		}
		else if (counter == 30)
		{
			printf("Task-1 priority lowers by 1");
			vTaskPrioritySet(xTask1Handle, uxTaskPriorityGet(xTask1Handle)+1);
			counter = 0;
		}
		//Dummy delay
		for(i=0; i<50000; i++);
	}
}
