/*
 * mytasks.h
 *
 *  Created on: 14-Oct-2020
 *      Author: NAMAN
 */

#ifndef MYTASKS_H_
#define MYTASKS_H_

#include"stm32f4xx.h"
#include"FreeRTOS.h"
#include"task.h"
#include"queue.h"
#include"semphr.h"
#include"leds.h"
#include"buttons.h"
#include"lcd.h"
#include"usart.h"
#include"main.h"
#include"portmacro.h"
#define DEBOUNCECOUNTS 	10
extern xQueueHandle RxQueue, TxQueue;
void vLEDFlashTask(void *pvParameters);
void vButtonCheckTask(void *pvParameters);
void vButtonLEDsTask(void *pvParamaters);
void vLCDTask(void *pvParameters);
void vUSARTTask(void *pvParameters);


#endif /* MYTASKS_H_ */
