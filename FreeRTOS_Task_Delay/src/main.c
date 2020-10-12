/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
//Description- In this program freertos task execute after 1 sec using delay means this task will goes into block state for every 1 sec duration

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
{ printf("Clock Task start Runing...\n");
	while(1)
	{
		printf("seconds count:%d\n", counter++);

		//provide 1 sec delay

		vTaskDelay(1000/ portTICK_PERIOD_MS);

	}
}
