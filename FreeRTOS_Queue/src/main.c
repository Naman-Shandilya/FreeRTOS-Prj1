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
#include"Queue.h"

void vTxTask1(void * pvParams);
void vTxTask2(void * pvParams);
void vRxTask(void * pvParams);

QueueHandle_t qHandle;

const char *t1_Msg = "Task-1 Message...";
const char *t2_Msg = "Task-2 Message...";


int main(void)
{
	RCC_DeInit();

	SystemCoreClockUpdate();

	qHandle = xQueueCreate(1, sizeof(char *));




	if(qHandle != NULL)
	{
		xTaskCreate (vTxTask1, "Tx1", 150, NULL, 1, NULL);

		xTaskCreate (vTxTask2, "Tx2", 150, NULL, 1, NULL);

		xTaskCreate (vRxTask, "Rx1", 200, NULL, 2, NULL);

		vTaskStartScheduler();

	}
	else
	{

	    printf ("Failed to create Queue! :-(\n");
	    while (1);
	}



}


void vTxTask1(void * pvParams)
{
	volatile int i = 0;

	int txStatus = 0;
	while(1)
	{
		printf("Sending Msg-Task-1\n");
		txStatus = xQueueSendToBack(qHandle, &t1_Msg, 2);

		if(txStatus == 0)
		{
			printf("Sending failed Task-1!\n");
		}
		for(i =0; i < 50000; i++);
	}
}
void vTxTask2(void * pvParams)
{
	volatile int i = 0;

	int txStatus = 0;
	while(1)
	{
		printf("Sending Msg-Task-2\n");
		txStatus = xQueueSendToBack(qHandle, &t2_Msg, 2);

		if(txStatus == 0)
		{
			printf("Sending failed Task-2!\n");
		}
		for(i =0; i < 50000; i++);
	}
}
void vRxTask(void * pvParams)
{
	volatile unsigned int i = 0;
	char * msgPtr;

	int rxStatus = 0;
	while(1)
	{
		rxStatus = xQueueReceive(qHandle, &msgPtr, 500);

		if(0 == rxStatus)
		{
			printf("Awaiting Message...\n");
		}
		else
		{
			printf("Rx Msg: %s\n", msgPtr);
		}
	}
}












