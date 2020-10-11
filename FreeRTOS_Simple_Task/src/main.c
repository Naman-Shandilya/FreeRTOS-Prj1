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



	for(;;);
}
