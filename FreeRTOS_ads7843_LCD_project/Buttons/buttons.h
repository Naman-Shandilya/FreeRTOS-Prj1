/*
 * buttons.h
 */
#ifndef BUTTONS_H_
#define BUTTONS_H_

#include"stm32f4xx.h"

#define BWAKEUP							GPIO_Pin_0
#define BWAKEUPPORT						GPIOA
#define BWAKEUPPORTCLK					RCC_AHB1Periph_GPIOA
#define BWAKEUPPINSOURCE				EXTI_PinSource0
#define BWAKEUPPORTSOURCE				EXTI_PortSourceGPIOA

#define BTAMPER							GPIO_Pin_13
#define BTAMPERPORT						GPIOC
#define BTAMPERPORTCLK					RCC_AHB1Periph_GPIOC
#define BTAMPERPINSOURCE				EXTI_PinSource13
#define BTAMPERPORTSOURCE				EXTI_PortSourceGPIOC

#define BUSER1							GPIO_Pin_8
#define BUSER1PORT						GPIOA
#define BUSER1PORTCLK					RCC_AHB1Periph_GPIOA
#define BUSER1PINSOURCE					EXTI_PinSource8
#define BUSER1PORTSOURCE				EXTI_PortSourceGPIOA

#define BUSER2							GPIO_Pin_3
#define BUSER2PORT						GPIOD
#define BUSER2PORTCLK					RCC_AHB1Periph_GPIOD
#define BUSER2PINSOURCE					EXTI_PinSource3
#define BUSER2PORTSOURCE				EXTI_PortSourceGPIOD


void ButtonsInit(void);
void ButtonsInitEXTI(void);
uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button);
void ButtonSetStatus(uint32_t status);
void ButtonResetStatus(void);
uint32_t ButtonGetStatus(void);



#endif //BUTTONS_H_
