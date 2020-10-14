#ifndef _ADS7843DRV_H_
#define _ADS7843DRV_H_

#include"stm32f4xx.h"

#define	CHX 	0x90
#define	CHY 	0xd0

/*
#define MASK_CS		(1<<16)
#define MASK_DCLK	(1<<17)
#define MASK_DIN	(1<<18)

#define MASK_INT	(1<<19)
#define MASK_DOUT	(1<<20)
 */





#define TP_DCLK(a)      \
                                                if (a)  \
                                                GPIOB->ODR |=(1<<13);\
                                                else            \
                                                GPIOB->ODR &=~(1<<13)

#define TP_CS(a)        \
                                                if (a)  \
                                                GPIOB->ODR |=(1<<12);\
                                                else            \
                                                GPIOB->ODR &=~(1<<12)
#define TP_DIN(a)       \
                                                if (a)  \
                                                GPIOB->ODR |=(1<<15);\
                                                else            \
                                                GPIOB->ODR &=~(1<<15)
// b0 int b1 busy a6 miso a7 mosi  a5 sck a4 t_cs

#define TP_DOUT  (GPIOB->IDR & (1<<14))  //MISO GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//( IOPIN1 & MASK_DOUT )
#define TP_BUSY  (GPIOG->IDR & (1<<8))  //      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//( IOPIN1 & MASK_DOUT )
#define TP_INT_IN   (GPIOG->IDR &(1<<7)) //( IOPIN1 & MASK_INT )




void TP_Init(void);
void TP_GetAdXY(int *x,int *y);

#endif


