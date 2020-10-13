/*
 * buttons.c
 */

#include"buttons.h"
static volatile uint32_t buttonStatus = 0;

void ButtonSetStatus(uint32_t status)
{
	buttonStatus = status;
}

void ButtonResetStatus(void)
{
	buttonStatus = 0;
}

uint32_t ButtonGetStatus(void)
{
	uint32_t temp;
	temp = buttonStatus;
	ButtonResetStatus();

	return temp;
}

void ButtonsInit(void)
{
	//Initialize the GPIO structure
	GPIO_InitTypeDef GPIO_InitStructure;
	//Enable the AHB1 peripheral clock
	RCC_AHB1PeriphClockCmd(BWAKEUPPORTCLK|BTAMPERPORTCLK|BUSER1PORTCLK|BUSER2PORTCLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = BWAKEUP|BUSER1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(BWAKEUPPORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = BTAMPER;
	GPIO_Init(BTAMPERPORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = BUSER2;
	GPIO_Init(BUSER2PORT, &GPIO_InitStructure);
}

void ButtonsInitEXTI(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//enabling the SYSCFG clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//enable the exti controller  clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);
	SYSCFG_EXTILineConfig(BWAKEUPPORTSOURCE, BWAKEUPPINSOURCE);
	SYSCFG_EXTILineConfig(BTAMPERPORTSOURCE, BTAMPERPINSOURCE);
	SYSCFG_EXTILineConfig(BUSER1PORTSOURCE, BUSER1PINSOURCE);
	SYSCFG_EXTILineConfig(BUSER2PORTSOURCE, BUSER2PINSOURCE);

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure);

	//select NVIC channel
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}

uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button)
{
	return !GPIO_ReadInputDataBit(Button_Port, Button);
}
