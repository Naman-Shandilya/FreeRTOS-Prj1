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
#include <stdint.h>
#include <stdio.h>


#define	__setbit(__reg, __bit)			((__reg) | = (1U << (__bit)))

#define	__clearbit(__reg, __bit)		((__reg) & = (~(1U << (__bit))))

#define __togglebit(__reg, __bit)		((__reg) ^ = (1U << (__bit)))

#define __getbit(__reg, __bit)			(((__reg) & (1U << (__bit))) >> (__bit))

void configureLEDs(void);

void myTask1(void *pvParameters);
void myTask2(void *pvParameters);

void vPortSetupTimerInterrupt(void);
extern void xPortSysTickHandler(void);

			

int main(void)
{
	NVIC_SetPriorityGrouping(0U);

	NVIC_SetPriority(TIM2_IRQn, 0xff);


	configureLEDs();

	xTaskCreate(myTask1, "Task1", 50, NULL, 1, NULL);
	xTaskCreate(myTask2, "Task2", 50, NULL, 1, NULL);

	vTaskStartScheduler();

	for(;;);
}

void vPortSetupTimerInterrupt(void)
{
	__setbit(RCC->APB1ENR, 0U);

	TIM2->PSC = 1000;

#if (UP_COUNTER)
	__clearbit(TIM2->CR1, 4U);
#else
	__clearbit(TIM2->CR1, 4U);
#endif
	 /*
	        As configTICK_RATE_HZ = 1000, so tick timer
	        need to generate interrupt at the rate of 1000/sec (1msec delay).
	        As the input frequency is 16khz so the total
	        counts required for 1msec delay:

	        total counts = 1msec * f
	                     =  0.001 * 16,000
	                     = 16
	    */
	    TIM2->ARR = 16;

	    /*
	        Enable timer-2 Update interrupt to
	        generate interrupt on counter overflow/underflow
	    */
	    __setbit(TIM2->DIER, 0U);


	    /*
	        Timer-2 interrupt is received on IRQ-6 on NVIC
	        so enable IRQ-6 on NVIC for interrupt detection
	    */
	     NVIC_EnableIRQ(TIM2_IRQn);

	     /* Start Timer-2 */
	     __setbit(TIM2->CR1, 0U);

}

void TIM2_IRQHandler(void){
	__clearbit(TIM2->SR, 0U);

	//call the freertos kernel for a tick update
	xPortSysTickHandler();
}

void myTask1(void *pvParameters)
{
	__IO uint i = 0;

	while(1)
	{
		__togglebit(GPIOD->ODR, 14);

		for(i=0; i< 500000; i++);
	}
}

void myTask2(void *pvParameters)
{
	__IO uint i = 0;

	while(1)
	{
		__togglebit(GPIO->ODR, 15);
		for(i = 0; i < 250000; i++);
	}
}

void configureLEDs(void)
{
	__setbit(RCC->AHB1ENR, 3);

	__setbit(GPIOD->MODER, 30);
	__clearbit(GPIOD->MODER, 31);

	__clearbit(GPIOD->OTYPER, 15);

	__setbit(GPIOD->OSPEEDR, 30);
	__clearbit(GPIOD->OSPEEDR, 31);

	__clearbit(GPIOD->PUPDR, 30);
	__clearbit(GPIOD->PUPDR, 31);

	 __setbit(GPIOD->MODER, 28);
	 __clearbit(GPIOD->MODER, 29);

	 __clearbit(GPIOD->OTYPER, 14);

	 __setbit(GPIOD->OSPEEDR, 28);
	 __clearbit(GPIOD->OSPEEDR, 29);

	 __clearbit(GPIOD->PUPDR, 28);
	 __clearbit(GPIOD->PUPDR, 29);
}
