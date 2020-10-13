/*
 * leds.h
 */
#ifndef LEDS_H_
#define LEDS_H_
#include"stm32f4xx.h"
#define LED1		GPIO_Pin_6
#define LED2		GPIO_Pin_7
#define LED3		GPIO_Pin_8
#define LED4		GPIO_Pin_9
#define LED5		GPIO_Pin_10
#define LEDPORT		GPIOF
#define LEDPORTCLK	RCC_APB2Periph_GPIOF

//function prototypes
void LEDsInit(void);
void LEDOn(uint32_t);
void LEDOff(uint32_t);
void LEDToggle(uint32_t);
#endif //LEDS_H_
