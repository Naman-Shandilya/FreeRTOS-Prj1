/*
 * usart.c
 */

#include"usart.h"
#include"mytask.h"
#define serPUT_STRING_CHAR_DELAY	(5 / portTICK_RATE_MS)
DMA_InitTypeDef  DMA_InitStructure;


void Usart2Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	// Peripheral Clock Enable--------------
	// Enabling the GPIO clock--------------
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// Enabling the USART clock-------------
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	//Enabling The DMA clock---------------
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	//USART2 GPIO configuration------------

	//Connect USART pin to AF7-------------
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //Tx Pin AF Configuration
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //Rx Pin AF Configuration

	// Configure USART Txand Rx as alternate function push-pull
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// USART2 Configuration--------------
	// Enable the USART Oversampling by 8------------
	USART_OverSampling8Cmd(USART2, ENABLE);

	/* USARTx configured as follows:
	        - BaudRate = 5250000 baud
			   - Maximum BaudRate that can be achieved when using the Oversampling by 8
			     is: (USART APB Clock / 8)
				 Example:
				    - (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
				    - (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
			   - Maximum BaudRate that can be achieved when using the Oversampling by 16
			     is: (USART APB Clock / 16)
				 Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
				 Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
	        - Word Length = 8 Bits
	        - one Stop Bit
	        - No parity
	        - Hardware flow control disabled (RTS and CTS signals)
	        - Receive and transmit enabled
	  */

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	//Configure DMA controller to manage USART TX and RX request-------

	// Configure DMA initialization Structure
	DMA_InitStructure.DMA_BufferSize = BUFFERSIZE;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(USART2->DR));
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	//Configuring TX DMA---------------
	DMA_InitStructure.DMA_Channel = DMA_Channel_6;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)TxBuffer;
	DMA_Init(DMA1_Stream3, &DMA_InitStructure);
	//Configure RX DMA-----------------
	DMA_InitStructure.DMA_Channel = DMA_Channel_5;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RxBuffer;
	DMA_Init(DMA1_Stream3, &DMA_InitStructure);

	//Enable USART2
	USART_Cmd(USART2, ENABLE);
	USART_DMACmd()(USART2,(USART_DMAReq_Tx | USART_DMAReq_Rx), ENABLE);

	//Configure NVIC
	NVIC_InitTypeDef NVIC_InitStructure;

	//Select NVIC Channel
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	//set priority to lowest
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	//set sub priority to lowest
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	//enable IRQ channel
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//update NVIC registers
	NVIC_Init(&NVIC_InitStructure);
	//disable transmit data register empty interrupt
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
	//enable receive data register not empty interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

uint32_t Usart2PutChar(char ch)
{
	if( xQueueSend( TxQueue, &ch, 10) == pdPASS)
	{
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		return pdTRUE;
	}
	else
	{
		return pdFAIL;
	}
}

void USART2PutString(const char * const pcString, unsigned long ulStringLength)
{
	unsigned long ul;
	for( ul =0; ul < ulStringLength; ul++)
	{
		if( xQueueSend(TxQueue, &(pcString[ul]), serPUT_STRING_CHAR_DELAY ) != pdPASS)
		{
			//Cannot fit any more in the queue try turning the tx on to clear some space
			USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
			vTaskDelay( serPUT_STRING_CHAR_DELAY);

			//Go Back and Try again
			continue;
		}
	}
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

uint32_t UsartGetChar(char *ch)
{
	if(xQueueReceive( RxQueue, ch, 0) == pdPASS)
	{
		return pdTRUE;
	}
	return pdFALSE;
}
