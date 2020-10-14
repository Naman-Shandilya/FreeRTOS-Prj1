/*
 * spi_flash.h
 */

#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include"stm32f4xx.h"

#define GPIO_CS							GPIOB
#define RCC_APB2Periph_GPIO_CS			RCC_APB2Periph_GPIOB
#define GPIO_Pin_CS						GPIO_Pin_2

//Exported macro-----------
//Select SPI Flash: Chip Select pin low------
#define SPI_FLASH_CS_LOW()				GPIO_ResetBits(GPIO_CS, GPIO_Pin_CS)

//Deselect SPI flash: Chip select pin high----------
#define SPI_FLASH_CS_HIGH()				GPIO_SetBits(GPIO_CS, GPIO_Pin_CS)

//Exported Functions--------------------
//-----------High Layer Functions-------------
void SPI_FLASH_Init(void);
void SPI_FLASH_SectorErase(uint32_t SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t SPI_FLASH_ReadID(void);
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);

//-----------Low Layer Function-----------------
uint8_t SPI_FLASH_ReadByte(void);
uint8_t SPI_FLASH_SEndByte(uint8_t byte);
uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);














#endif //__SPI_FLASH_H
