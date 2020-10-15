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
#include"queue.h"
#include<stdint.h>
#include<stdio.h>
#include"semphr.h"

#define	__setbit(__reg, __bit)			((__reg) | = (1U << (__bit)))

#define	__clearbit(__reg, __bit)		((__reg) & = (~(1U << (__bit))))

#define __togglebit(__reg, __bit)		((__reg) ^ = (1U << (__bit)))

#define __getbit(__reg, __bit)			(((__reg) & (1U << (__bit))) >> (__bit))

//QueueHandle_t 	qHandle;

SemaphoreHandle_t smphrHandle;

const char *t1_Msg = "Message received from button ISR";

//void vRxTask(void * pvParams);
void vTask (void *);

static void configInputPin(void);
			

int main(void)
{
	__IO unsigned int i = 0;

	configInputPin();

	__setbit(RCC->APB2ENR, 14);

	__clearbit(SYSCFG-> EXTICR[0], 0);
	__clearbit(SYSCFG-> EXTICR[0], 1);
	__clearbit(SYSCFG-> EXTICR[0], 2);
	__clearbit(SYSCFG-> EXTICR[0], 3);

	__setbit(EXTI->IMR, 0);

	__setbit(EXTI->RTSR, 0);

	NVIC_SetPriority(EXTI0_IRQn, 6U);

	NVIC_EnableIRQ(EXTI0_IRQn);

	//qHandle = xQueueCreate(2, sizeof(char *));

	smphrHandle = xSemaphoreCreateBinary();

	if(smphrHandle != NULL)
	{
		xTaskCreate(vRxTask, "Task", 200, NULL, 1, NULL);

		vTaskStartScheduler();
	}
	else
	{
		printf ("Failed to create Queue! :-\n");
		while(1);
	}
}

static void configInputPin(void)
{
	__setbit(RCC->AHB1ENR, 0);

	__clearbit(GPIOA->MODER, 0);
	__clearbit(GPIOA->MODER, 1);

	__clearbit(GPIOA->OTYPER, 0);

	__setbit(GPIOA->OSPEEDR, 0);
	__clearbit(GPIOA->OSPEEDR, 1);

	__clear(GPIOA->PUPDR, 0);
	__setbit(GPIOA->PUPDR, 1);
}

/*void vRxTask(void *pvParams)
{
	__IO uint i = 0;
	char * msgPtr;

	int rxStatus = 0;
	for(;;)
	{
		rxStatus = xQueueReceive(qHandle, &msgPtr, 500);

		if(0 == rxStatus)
		{
			printf("Awaiting Message....\n");
		}
		else
		{
			printf("Rx Msg: %s\n", msgPtr);
		}
	}
}
*/

void vTask(void * pvParams)
{
	//initially take semaphore to bring the binary semaphore counter value to 0
	xSemaphoreTake(smphrHandle, portMAX_DELAY);

	while(1)
	{
		//task locked here until unlock by isr
		xSemaphoreTake(smphrHandle, portMAX_DELAY);

		printf("ButtonPressed, Task Unlocked\n");
	}
}

void EXTI0_IRQHandler(void)
{
	int txStatus = 0;

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	__setbit(EXTI->PR, 0);

	printf("Button Pressed, Sending Message to queue\n");

	txStatus = xSemaphoreGive(smphrHandle, &xHigherPriorityTaskWoken);

	if(0 == txStatus)
	{
		printf("Sending Failed Task-1\n");
	}
	else
	{
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
	}


}
