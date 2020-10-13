/*
 * usart.h
 */

#ifndef USART_H_
#define USART_H_

#include"stm32f4xx.h"
void Usart2Init(void);
uint32_t Usart2GetChar(char *ch);
uint32_t Usart2PutChar(char ch);
void USART2PutString(const char * const pcString, unsigned long ulStringLength);


#endif /* USART_H_ */
