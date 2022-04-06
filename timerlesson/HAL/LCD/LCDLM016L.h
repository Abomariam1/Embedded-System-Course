/*
* LCDLM016L.h
*
* Created: 17/03/2022 07:12:17 م
*  Author: PC
*/


#ifndef LCDLM016L_H_
#define LCDLM016L_H_

#include "../../MCAL_Registers/MEM_MapAvr328P.h"
#include "../../Helpers/Std_Types.h"
#include "../../Helpers/Utils.h"
#include "../../MCAL/GPIO/GPIO_AVR328P.h"


//#define HIGHER_NIBBLE_VALUE(REG,DATA)                   (REG)=(REG&0x0f)|(DATA&0XF0)
#define Clear_LCD					0x01
#define Return_Home					0x02
#define Dec_Cursor					0x04
#define Inc_Cursor					0x06
#define Shift_Disp_right			0x05
#define Shift_Disp_Left				0x07
#define Disp_Off_Cursor_Off			0x08
#define Disp_Off_Cursor_On			0x0A
#define Disp_ON_Cursor_Off			0x0C
#define Disp_On_Cursor_Blink		0x0E
#define Shift_Pos_Left				0x10
#define Shift_Pos_Right				0x14
#define Shift_Ent_To_Left			0x18
#define Shift_Ent_To_Right			0x1C
#define Forc_1ST					0x80
#define Forc_2ST					0xC0
#define Tow_Lines_4Bit				0x28
#define Tow_Lines_8Bit				0x38

//#define D4  PIN_4
//#define D5  PIN_5
//#define D6  PIN_6
//#define D7  PIN_7
//
//#define RS  PIN_1
//#define RW  PIN_2
//#define EN  PIN_3
//
//#define M_4BIT_SAMEPORT  0
//#define M_4BIT_SEPARATED 1
//#define M_8BIT           2

#define M_4BIT_MASK 0Xf0

typedef enum PINS
{
	PN0,
	PN1,
	PN2,
	PN3,
	PN5,
	PN6,
	PN7
}PINS_t;

typedef enum LCDMode{
	M_4BIT_SAMEPORT,
	M_4BIT_SEPARATED,
	M_8BIT
}LCDMode_t;

typedef struct LcdInit{
	LCDMode_t Mode;
	uint8 RSPin;
	uint8 EnPin;
	GPIO_port_name_t DataPort;
	GPIO_port_name_t cmdport;
	uint8 PortVal;
}LcdInit_t;

extern void Lcd_Init(LcdInit_t *LcdPort);

extern void LCD_WriteChar(uint8 character);

static void LCD_WriteCommand(uint8 Command);

static void LatchRs(void);

static void LCD_SendData(uint8 data);

static void Lcd_Init2();

#endif /* LCDLM016L_H_ */