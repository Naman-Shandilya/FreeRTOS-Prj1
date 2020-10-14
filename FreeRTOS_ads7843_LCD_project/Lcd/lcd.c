/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : lcd.c
* Author             : MCD Application Team
* Version            : V1.1.2
* Date               : 09/22/2008
* Description        : This file includes the LCD driver for AM-240320L8TNQW00H 
*                     (LCD_ILI9320) Liquid Crystal Display Module of STM3210E-EVAL
*                      board.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "fonts.h"
//static vu32 TimingDelay = 0;
/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  vu16 LCD_REG;
  vu16 LCD_RAM;
} LCD_TypeDef;

/* Note: LCD /CS is CE4 - Bank 4 of NOR/SRAM Bank 1~4 */
#define LCD_BASE        ((u32)(0x60000000 | 0x0C000000))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/                              
/* Private variables ---------------------------------------------------------*/
  /* Global variables to set the written text color */
static vu16 TextColor = 0x0000, BackColor = 0xFFFF;

u16 DeviceCode;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : LCD_Init
* Description    : Initializes the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Init(void)
{ 
/* Configure the LCD Control pins --------------------------------------------*/
  LCD_CtrlLinesConfig();

/* Configure the FSMC Parallel interface -------------------------------------*/
  LCD_FSMCConfig();

  Delay(5); /* delay 50 ms */
  Delay(5); /* delay 50 ms */
  // Start Initial Sequence
  DeviceCode = LCD_ReadReg(0x0000);
//#ifdef	ILI9320
  if(DeviceCode == 0x9320) 		//3.2�
  {
	  Delay(5); /* delay 50 ms */
	/* Start Initial Sequence ----------------------------------------------------*/
	  LCD_WriteReg(R229,0x8000); /* Set the internal vcore voltage */
	  LCD_WriteReg(R0,  0x0001); /* Start internal OSC. */
	  LCD_WriteReg(R1,  0x0100); /* set SS and SM bit */
	  LCD_WriteReg(R2,  0x0700); /* set 1 line inversion */
	  LCD_WriteReg(R3,  0x1030); /* set GRAM write direction and BGR=1. */
	  LCD_WriteReg(R4,  0x0000); /* Resize register */
	  LCD_WriteReg(R8,  0x0202); /* set the back porch and front porch */
	  LCD_WriteReg(R9,  0x0000); /* set non-display area refresh cycle ISC[3:0] */
	  LCD_WriteReg(R10, 0x0000); /* FMARK function */
	  LCD_WriteReg(R12, 0x0000); /* RGB interface setting */
	  LCD_WriteReg(R13, 0x0000); /* Frame marker Position */
	  LCD_WriteReg(R15, 0x0000); /* RGB interface polarity */

	/* Power On sequence ---------------------------------------------------------*/
	  LCD_WriteReg(R16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	  LCD_WriteReg(R17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
	  LCD_WriteReg(R18, 0x0000); /* VREG1OUT voltage */
	  LCD_WriteReg(R19, 0x0000); /* VDV[4:0] for VCOM amplitude */
	  Delay(20);                 /* Dis-charge capacitor power voltage (200ms) */
	  LCD_WriteReg(R16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	  LCD_WriteReg(R17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
	  Delay(5);                  /* Delay 50 ms */
	  LCD_WriteReg(R18, 0x0139); /* VREG1OUT voltage */
	  Delay(5);                  /* Delay 50 ms */
	  LCD_WriteReg(R19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
	  LCD_WriteReg(R41, 0x0013); /* VCM[4:0] for VCOMH */
	  Delay(5);                  /* Delay 50 ms */
	  LCD_WriteReg(R32, 0x0000); /* GRAM horizontal Address */
	  LCD_WriteReg(R33, 0x0000); /* GRAM Vertical Address */

	/* Adjust the Gamma Curve ----------------------------------------------------*/
	  LCD_WriteReg(R48, 0x0006);
	  LCD_WriteReg(R49, 0x0101);
	  LCD_WriteReg(R50, 0x0003);
	  LCD_WriteReg(R53, 0x0106);
	  LCD_WriteReg(R54, 0x0b02);
	  LCD_WriteReg(R55, 0x0302);
	  LCD_WriteReg(R56, 0x0707);
	  LCD_WriteReg(R57, 0x0007);
	  LCD_WriteReg(R60, 0x0600);
	  LCD_WriteReg(R61, 0x020b);

	/* Set GRAM area -------------------------------------------------------------*/
	  LCD_WriteReg(R80, 0x0000); /* Horizontal GRAM Start Address */
	  LCD_WriteReg(R81, 0x00EF); /* Horizontal GRAM End Address */
	  LCD_WriteReg(R82, 0x0000); /* Vertical GRAM Start Address */
	  LCD_WriteReg(R83, 0x013F); /* Vertical GRAM End Address */

	  LCD_WriteReg(R96,  0xA700); /* 3.2-->9320->0xA700 Gate Scan Line */

	  LCD_WriteReg(R97,  0x0001); /* NDL,VLE, REV */
	  LCD_WriteReg(R106, 0x0000); /* set scrolling line */

	/* Partial Display Control ---------------------------------------------------*/
	  LCD_WriteReg(R128, 0x0000);
	  LCD_WriteReg(R129, 0x0000);
	  LCD_WriteReg(R130, 0x0000);
	  LCD_WriteReg(R131, 0x0000);
	  LCD_WriteReg(R132, 0x0000);
	  LCD_WriteReg(R133, 0x0000);

	/* Panel Control -------------------------------------------------------------*/
	  LCD_WriteReg(R144, 0x0010);
	  LCD_WriteReg(R146, 0x0000);
	  LCD_WriteReg(R147, 0x0003);
	  LCD_WriteReg(R149, 0x0110);
	  LCD_WriteReg(R151, 0x0000);
	  LCD_WriteReg(R152, 0x0000);

	  /* Set GRAM write direction and BGR = 1 */
	  /* I/D=01 (Horizontal : increment, Vertical : decrement) */
	  /* AM=1 (address is updated in vertical writing direction) */
	  LCD_WriteReg(R3, 0x1018);

	  LCD_WriteReg(R7, 0x0173); /* 262K color and display ON */

	  Delay(5); /* delay 50 ms */
	  Delay(5); /* delay 50 ms */			//start internal osc
	}
//#endif
//#ifdef	ILI9325			//2.8' display
  else {
	Delay(5); /* delay 50 ms */
	  Delay(5); /* delay 50 ms */
	  // Start Initial Sequence
	  LCD_WriteReg(0x00FF,0x0001);
	  LCD_WriteReg(0x00F3,0x0008);
	  LCD_WriteReg(0x0001,0x0100);
	  LCD_WriteReg(0x0002,0x0700);
	  LCD_WriteReg(0x0003,0x1030);  //0x1030
	  LCD_WriteReg(0x0008,0x0302);
	  LCD_WriteReg(0x0008,0x0207);
	  LCD_WriteReg(0x0009,0x0000);
	  LCD_WriteReg(0x000A,0x0000);
	  LCD_WriteReg(0x0010,0x0000);  //0x0790
	  LCD_WriteReg(0x0011,0x0005);
	  LCD_WriteReg(0x0012,0x0000);
	  LCD_WriteReg(0x0013,0x0000);
	  Delay(5);
	  LCD_WriteReg(0x0010,0x12B0);
	  Delay(5);
	  LCD_WriteReg(0x0011,0x0007);
	  Delay(5);
	  LCD_WriteReg(0x0012,0x008B);
	  Delay(5);
	  LCD_WriteReg(0x0013,0x1700);
	  Delay(5);
	  LCD_WriteReg(0x0029,0x0022);
			
	  //################# void Gamma_Set(void) ####################//
	  LCD_WriteReg(0x0030,0x0000);
	  LCD_WriteReg(0x0031,0x0707);
	  LCD_WriteReg(0x0032,0x0505);
	  LCD_WriteReg(0x0035,0x0107);
	  LCD_WriteReg(0x0036,0x0008);
	  LCD_WriteReg(0x0037,0x0000);
	  LCD_WriteReg(0x0038,0x0202);
	  LCD_WriteReg(0x0039,0x0106);
	  LCD_WriteReg(0x003C,0x0202);
	  LCD_WriteReg(0x003D,0x0408);
	  Delay(5);
			
	  LCD_WriteReg(0x0050,0x0000);		
	  LCD_WriteReg(0x0051,0x00EF);		
	  LCD_WriteReg(0x0052,0x0000);		
	  LCD_WriteReg(0x0053,0x013F);		
	  LCD_WriteReg(0x0060,0x2700);		
	  LCD_WriteReg(0x0061,0x0001);
	  LCD_WriteReg(0x0090,0x0033);				
	  LCD_WriteReg(0x002B,0x000B);		
	  LCD_WriteReg(0x0007,0x0133);
	  Delay(5);
	}
//#endif
}

/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : Clears the hole LCD.
* Input          : Color: the color of the background.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Clear(u16 Color)
{
  u32 index = 0;
  
  LCD_SetCursor(0x00, 0x013F); 

  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

  for(index = 0; index < 76800; index++)
  {
	  LCD_WriteRAM(Color);
    //LCD->LCD_RAM = Color;
  }  
}

/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position. 
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetCursor(u8 Xpos, u16 Ypos)
{
  LCD_WriteReg(R32, Xpos);
  LCD_WriteReg(R33, Ypos);
}

/*******************************************************************************
* Function Name  : LCD_SetDisplayWindow
* Description    : Sets a display window
* Input          : - Xpos: specifies the X buttom left position.
*                  - Ypos: specifies the Y buttom left position.
*                  - Height: display window height.
*                  - Width: display window width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetDisplayWindow(u8 Xpos, u16 Ypos, u8 Height, u16 Width)
{
  /* Horizontal GRAM Start Address */
  LCD_WriteReg(R80, Xpos);

  /* Horizontal GRAM End Address */
  LCD_WriteReg(R81, Xpos+Height);
 
  /* Vertical GRAM Start Address */
  LCD_WriteReg(R82, Ypos);

  /* Vertical GRAM End Address */
  LCD_WriteReg(R83, Ypos+Width);

  LCD_SetCursor(Xpos, Ypos);
}

/*******************************************************************************
* Function Name  : LCD_WriteBMP
* Description    : Displays a bitmap picture loaded in the internal Flash.
* Input          : - BmpAddress: Bmp picture address in the internal Flash.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteBMP_Dim(u8 Xpos, u16 Ypos, u8 Height, u16 Width, u8 *bitmap)
{
  vu32 index;
  vu32 size = Height * Width;
  u16 *bitmap_ptr = (u16 *)bitmap;

  LCD_SetDisplayWindow(Xpos, Ypos, Height-1, Width-1);

  /* Set GRAM write direction and BGR = 1 */
  /* I/D=11 (Horizontal : increment, Vertical : increment) */
  /* AM=1 (address is updated in vertical writing direction) */
  LCD_WriteReg(R3, 0x1038);
 
  LCD_WriteRAM_Prepare();
 
  for(index = 0; index < size; index++)
  {
	LCD_WriteRAM(*bitmap_ptr++);
  }
 
  /* Set GRAM write direction and BGR = 1 */
  /* I/D = 01 (Horizontal : increment, Vertical : decrement) */
  /* AM = 1 (address is updated in vertical writing direction) */
  LCD_WriteReg(R3, 0x1018);
  LCD_SetDisplayWindow(00, 00, 239, 319);
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
}

/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
*******************************************************************************/
u16 LCD_ReadReg(u16 LCD_Reg)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = LCD_Reg;
  LCD->LCD_RAM;
  /* Read 16-bit Reg */
  return (LCD->LCD_RAM);
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
* Description    : Prepare to write to the LCD RAM.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
  LCD->LCD_REG = R34;
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)
{
  /* Write 16-bit GRAM Reg */
  LCD->LCD_RAM = RGB_Code;
}

/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
*******************************************************************************/
u16 LCD_ReadRAM(void)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = R34; /* Select GRAM Reg */
  /* Read 16-bit Reg */
  return LCD->LCD_RAM;
}

/*******************************************************************************
* Function Name  : LCD_PowerOn
* Description    : Power on the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PowerOn(void)
{
/* Power On sequence ---------------------------------------------------------*/
  LCD_WriteReg(R16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WriteReg(R17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
  LCD_WriteReg(R18, 0x0000); /* VREG1OUT voltage */
  LCD_WriteReg(R19, 0x0000); /* VDV[4:0] for VCOM amplitude*/
  Delay(20);             /* Dis-charge capacitor power voltage (200ms) */
  LCD_WriteReg(R16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WriteReg(R17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
  Delay(5);              /* Delay 50 ms */
  LCD_WriteReg(R18, 0x0139); /* VREG1OUT voltage */
  Delay(5);              /* Delay 50 ms */
  LCD_WriteReg(R19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
  LCD_WriteReg(R41, 0x0013); /* VCM[4:0] for VCOMH */
  Delay(5);              /* Delay 50 ms */
  LCD_WriteReg(R7, 0x0173);  /* 262K color and display ON */
}

/*******************************************************************************
* Function Name  : LCD_DisplayOn
* Description    : Enables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOn(void)
{
  /* Display On */
  LCD_WriteReg(R7, 0x0173); /* 262K color and display ON */
}

/*******************************************************************************
* Function Name  : LCD_DisplayOff
* Description    : Disables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOff(void)
{
  /* Display Off */
  LCD_WriteReg(R7, 0x0); 
}

/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD Control lines (FSMC Pins) in alternate function
                   Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE |
                         RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG |
                         RCC_AHB1Periph_AFIO, ENABLE);

  /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
     PD.10(D15), PD.14(D0), PD.15(D1) as alternate 
     function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
     PE.14(D11), PE.15(D12) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_SET);

  /* Set PF.00(A0 (RS)) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_FSMCConfig
* Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_FSMCConfig(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;

/*-- FSMC Configuration ------------------------------------------------------*/
/*----------------------- SRAM Bank 4 ----------------------------------------*/
  /* FSMC_Bank1_NORSRAM4 configuration */
  p.FSMC_AddressSetupTime = 0;
  p.FSMC_AddressHoldTime = 0;
  p.FSMC_DataSetupTime = 2;
  p.FSMC_BusTurnAroundDuration = 0;
  p.FSMC_CLKDivision = 0;
  p.FSMC_DataLatency = 0;
  p.FSMC_AccessMode = FSMC_AccessMode_A;

  /* Color LCD configuration ------------------------------------
     LCD configured as follow:
        - Data/Address MUX = Disable
        - Memory Type = SRAM
        - Data Width = 16bit
        - Write Operation = Enable
        - Extended Mode = Enable
        - Asynchronous Wait = enable */
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
  //Added FSMC_AsynchronousWait as mentioned Stdperiph library
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Enable;
  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  

  /* BANK 4 (of NOR/SRAM Bank 1~4) is enabled */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}

//

//
void LCD_SetTextColor(uint16_t Color)
{
	TextColor = Color;
}
void LCD_SetBackColor(uint16_t Color)
{
	BackColor = Color;
}
void LCD_ClearLine(uint8_t Line)
{

}
void LCD_DrawChar(uint8_t Xpos, uint16_t Ypos, const uint16_t *c)
{
	uint32_t index = 0, i = 0;
	  uint8_t Xaddress = 0;

	  Xaddress = Xpos;

	  LCD_SetCursor(Xaddress, Ypos);

	  for(index = 0; index < 24; index++)
	  {
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    for(i = 0; i < 16; i++)
	    {
	      if((c[index] & (1 << i)) == 0x00)
	      {
	        LCD_WriteRAM(BackColor);
	      }
	      else
	      {
	        LCD_WriteRAM(TextColor);
	      }
	    }
	    Xaddress++;
	    LCD_SetCursor(Xaddress, Ypos);
	  }

}
void LCD_DisplayChar(uint8_t Line, uint16_t Column, uint8_t Ascii)
{
	  Ascii -= 32;
	  LCD_DrawChar(Line, Column, &ASCII_Table[Ascii * 24]);
}
void LCD_DisplayStringLine(u8 Line, char *ptr, u16 charColor, u16 bkColor)
{
	  u32 i = 0;
	  u16 refcolumn = 0;

	  /* Send the string character by character on lCD */
	  while ((*ptr != 0) & (i < 40))
	  {
	    /* Display one character on LCD */
	//    LCD_PutChar(refcolumn, Line, *ptr, charColor, bkColor);
		LCD_PutChar(Line, refcolumn, *ptr, charColor, bkColor);
	    /* Decrement the column position by 16 */
	    refcolumn += 16;
	    /* Point on the next character */
	    ptr++;
	    /* Increment the character counter */
	    i++;
	  }
}
void LCD_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
	  u16 i=0;
	  u16 j=0;

	  u16 tmp_char=0;

	  for (i=0;i<24;i++)
	  {
	    tmp_char=ASCII_Table[((c-0x20)*24)+i];	 //��ȥ32��ƫ�ƣ�����Ϊ�ַ����ӿո�ʼ�ģ��ο��ַ����ǵ�ע��
	    for (j=0;j<16;j++)
	    {
	//      if ( (tmp_char >> 15-j) & 0x01 == 0x01)	�����������ʾ���ַ��ǵ������ģ�������Ĺ���������
		if ( (tmp_char >> j) & (0x01 == 0x01))
	      {
	        LCD_SetPoint(x+i,y+j,charColor); // �ַ���ɫ
	      }
	      else
	      {
	        LCD_SetPoint(x+i,y+j,bkColor); // ������ɫ
	      }
	    }
	  }
}
void LCD_SetPoint(u16 x,u16 y,u16 point)
{
	  if ( (x>240)||(y>360) ) return;

	  LCD_SetCursor(x,y);
	  LCD_WriteRAM_Prepare();
	  LCD_WriteRAM(point);
}
void LCD_WindowModeDisable(void)
{
	  LCD_SetDisplayWindow(239, 0x13F, 240, 320);
	  LCD_WriteReg(R3, 0x1018);
}
void LCD_DrawLine(uint8_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction)
{
	  uint32_t i = 0;

	  LCD_SetCursor(Xpos, Ypos);

	  if(Direction == Horizontal)
	  {
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    for(i = 0; i < Length; i++)
	    {
	      LCD_WriteRAM(TextColor);
	    }
	  }
	  else
	  {
	    for(i = 0; i < Length; i++)
	    {
	      LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	      LCD_WriteRAM(TextColor);
	      Xpos++;
	      LCD_SetCursor(Xpos, Ypos);
	    }
	  }
}
void LCD_DrawRect(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width)
{
	  LCD_DrawLine(Xpos, Ypos, Width, Horizontal);
	  LCD_DrawLine((Xpos + Height), Ypos, Width, Horizontal);

	  LCD_DrawLine(Xpos, Ypos, Height, Vertical);
	  LCD_DrawLine(Xpos, (Ypos - Width + 1), Height, Vertical);
}
void LCD_DrawCircle(uint8_t Xpos, uint16_t Ypos, uint16_t Radius)
{
	  int32_t  D;/* Decision Variable */
	  uint32_t  CurX;/* Current X Value */
	  uint32_t  CurY;/* Current Y Value */

	  D = 3 - (Radius << 1);
	  CurX = 0;
	  CurY = Radius;

	  while (CurX <= CurY)
	  {
	    LCD_SetCursor(Xpos + CurX, Ypos + CurY);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);

	    LCD_SetCursor(Xpos + CurX, Ypos - CurY);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);

	    LCD_SetCursor(Xpos - CurX, Ypos + CurY);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);

	    LCD_SetCursor(Xpos - CurX, Ypos - CurY);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);

	    LCD_SetCursor(Xpos + CurY, Ypos + CurX);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);

	    LCD_SetCursor(Xpos + CurY, Ypos - CurX);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);

	    LCD_SetCursor(Xpos - CurY, Ypos + CurX);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);

	    LCD_SetCursor(Xpos - CurY, Ypos - CurX);
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    LCD_WriteRAM(TextColor);

	    if (D < 0)
	    {
	      D += (CurX << 2) + 6;
	    }
	    else
	    {
	      D += ((CurX - CurY) << 2) + 10;
	      CurY--;
	    }
	    CurX++;
	  }

}
void LCD_DrawMonoPict(const uint32_t *Pict)
{
	  uint32_t index = 0, i = 0;

	  LCD_SetCursor(0, 319);

	  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	  for(index = 0; index < 2400; index++)
	  {
	    for(i = 0; i < 32; i++)
	    {
	      if((Pict[index] & (1 << i)) == 0x00)
	      {
	        LCD_WriteRAM(BackColor);
	      }
	      else
	      {
	        LCD_WriteRAM(TextColor);
	      }
	    }
	  }

}
void LCD_WriteBMP(uint32_t BmpAddress)
{
	  uint32_t index = 0, size = 0;

	  /* Read bitmap size */
	  size = *(__IO uint16_t *) (BmpAddress + 2);
	  size |= (*(__IO uint16_t *) (BmpAddress + 4)) << 16;

	  /* Get bitmap data address offset */
	  index = *(__IO uint16_t *) (BmpAddress + 10);
	  index |= (*(__IO uint16_t *) (BmpAddress + 12)) << 16;

	  size = (size - index)/2;

	  BmpAddress += index;

	  /* Set GRAM write direction and BGR = 1 */
	  /* I/D=00 (Horizontal : decrement, Vertical : decrement) */
	  /* AM=1 (address is updated in vertical writing direction) */
	  LCD_WriteReg(R3, 0x1008);

	  LCD_WriteRAM_Prepare();

	  for(index = 0; index < size; index++)
	  {
	    LCD_WriteRAM(*(__IO uint16_t *)BmpAddress);
	    BmpAddress += 2;
	  }

	  /* Set GRAM write direction and BGR = 1 */
	  /* I/D = 01 (Horizontal : increment, Vertical : decrement) */
	  /* AM = 1 (address is updated in vertical writing direction) */
	  LCD_WriteReg(R3, 0x1018);

}

//custom

void LCDDrawLine(uint16_t x1, uint16_t y1,	uint16_t x2, uint16_t y2, uint16_t color)
{
	int16_t dx, dy, stepx, stepy, fraction;

    dy = y2 - y1;
    dx = x2 - x1;
    if ( dy < 0 ) {
        dy    = -dy;
        stepy = -1;
    } else {
        stepy = 1;
    }
    if ( dx < 0 ) {
        dx    = -dx;
        stepx = -1;
    } else {
        stepx = 1;
    }
    dx <<= 1;
    dy <<= 1;
    LCD_SetPoint(x1,y1,color);
    if ( dx > dy ) {
        fraction = dy - ( dx >> 1);
        while ( x1 != x2 ) {
            if ( fraction >= 0 ) {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;
            LCD_SetPoint(x1,y1,color);
        }
    } else {
        fraction = dx - ( dy >> 1);
        while ( y1 != y2 ) {
            if ( fraction >= 0 ) {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;
            LCD_SetPoint(x1,y1,color);
        }
    }
}


/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
