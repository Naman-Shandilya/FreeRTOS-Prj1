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
#include<string.h>
#include<stdint.h>

//FUNCTION Prototype Definition
//Task function prototype Definition
void vTask1_Function(void* vparams);
void vTask2_Function(void* vparams);



//Task Handle Structure Variable
TaskHandle_t xTaskHandle1 = NULL;
TaskHandle_t xTaskHandle2 = NULL;
int main(void)
{
	//Before creating any project we should have to ask ourself that
	//What is the Frequency at which the main system clock of MCU is running?
	//And what is the source for that clock?
	//To check this refer to system_stm32f4xx.c file in src folder this tell the system clock of the mcu
	//Now to check the external crystal oscillator and internal oscillator default value we refer to stm32f4xx.h file in cmsis->device
	//so to run the cpu at default clock frequency we will deinit the clock control of mcu by using the following function

	RCC_DeInit();//here HSI-ON, HSE-OFF, PLL-OFF

	//Now update the system core clock to establish the changes made
	SystemCoreClockUpdate();

	//now lets create the task
	//task is basically a function itself it is a set of instructions and combination of other different functions that uses
	//mcu peripherals to perform some operations
	//A task is a function that will have an infinite loop so that it will never return runs in endless loop

	xTaskCreate(vTask1_Function, "Task-1", configMINIMAL_STACK_SIZE, NULL, 3, &xTaskHandle1);
	xTaskCreate(vTask2_Function, "Task-2", configMINIMAL_STACK_SIZE, NULL, 3, &xTaskHandle2);

	//to run the task using the RTOS we should have to start the scheduler
	//the task of scheduler is to start the task and the check the condition for the contex switching
	//this can be done by the systick timer, it means that when there is an systick interrupt this interrupt will cause the pendsv interrupt
	//which results in setting the pend bit of the current running task and changes the status of the running task to ready
	//contex switching can be done in many ways we will discuss about this thoroly in near future
	//so lets start our scheduler
	vTaskStartScheduler();



	for(;;);
}



void vTask1_Function(void* vparams)
{
	volatile uint16_t i = 0;
	while(1)
	{
		printf("Task-1 is running \r\n");

		//lets give some dummy delay
		for(i=0; i<50000; i++);
	}
}
void vTask2_Function(void* vparams)
{
	volatile uint16_t i = 0;
	while(1)
	{
		printf("Task-2 is running \r\n");

		//lets give some dummy delay
		for(i=0; i<50000; i++);
	}
}


