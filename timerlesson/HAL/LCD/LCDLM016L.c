/*
* LCDLM016L.c
*
* Created: 17/03/2022 07:12:47 م
*  Author: PC
*/
#include <util/delay.h>
#include "LCDLM016L.h"
#include "../../MCAL_Registers/MEM_MapAvr328P.h"
#include "../../Helpers/Std_Types.h"
#include "../../Helpers/Utils.h"
#include "../../MCAL/GPIO/GPIO_AVR328P.h"

/**************************************************************************/
static LcdInit_t *LCDOBj;
static uint8 pos = 0; 

void Lcd_Init(LcdInit_t *LcdPort)
{
	LCDOBj = LcdPort;
	_delay_ms(50);
	Lcd_Init2();
}

static void Lcd_Init2()
{
	switch (LCDOBj->Mode)
	{
		case  M_8BIT:
		GPIO_init_port(LCDOBj->DataPort,GPIO_OUTPUT); // data output
		GPIO_init_pin(LCDOBj->cmdport,LCDOBj->RSPin,GPIO_OUTPUT); // set rs pin output
		GPIO_init_pin(LCDOBj->cmdport,LCDOBj->EnPin,GPIO_OUTPUT); // set enable pin output
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->RSPin,LOW); // set rs pin in low
		LCD_WriteCommand(Tow_Lines_8Bit);
		_delay_ms(2);
		LCD_WriteCommand(Disp_On_Cursor_Blink);
		_delay_ms(2);
		LCD_WriteCommand(Clear_LCD);
		_delay_ms(2);
		break;

		case  M_4BIT_SAMEPORT:
		GPIO_init_port_mask(LCDOBj->DataPort,LCDOBj->PortVal); // data output
		LCD_WriteCommand(Return_Home);
		_delay_ms(2);
		LCD_WriteCommand(Tow_Lines_4Bit);
		_delay_ms(2);
		LCD_WriteCommand(Disp_ON_Cursor_Off);
		_delay_ms(2);
		LCD_WriteCommand(Clear_LCD);
		_delay_ms(2);
		LCD_WriteCommand(Inc_Cursor);
		LCD_WriteCommand(Forc_1ST);
		break;

		case  M_4BIT_SEPARATED:

		break;
	}
	
}

static void LCD_WriteCommand(uint8 Command)
{
	switch(LCDOBj->Mode)
	{
		case M_8BIT:
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->RSPin,LOW); //clear RS pin for send command
		GPIO_write_port(LCDOBj->DataPort,Command);// send command at the port
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->EnPin,HIGH);	 //set enable pin high
		_delay_us(2);
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->EnPin,LOW);
		_delay_us(2);
		break;

		case M_4BIT_SAMEPORT:	
		GPIO_write_port_mask_HN(LCDOBj->DataPort,Command); //send High Nibble command at high 4bit port	
		GPIO_write_pin(LCDOBj->DataPort,LCDOBj->RSPin,LOW); //clear RS pin for send command		
		GPIO_write_pin(LCDOBj->DataPort,LCDOBj->EnPin,HIGH); //set Enable Pin High
		_delay_ms(2);
		GPIO_write_pin(LCDOBj->DataPort,LCDOBj->EnPin,LOW); //set Enable Pin Low
		_delay_ms(2); 		
		 GPIO_write_port_mask_LN(LCDOBj->DataPort,Command); //send Low Nibble command at high 4bit port
		GPIO_write_pin(LCDOBj->DataPort,LCDOBj->EnPin,HIGH); //set Enable Pin High
		_delay_ms(2);
		GPIO_write_pin(LCDOBj->DataPort,LCDOBj->EnPin,LOW); //set Enable Pin Low
		_delay_ms(2);
		break;

		case M_4BIT_SEPARATED:

		break;
	}  
}  

static void LCD_SendData(uint8 data)
{
	switch(LCDOBj->Mode)
	{
		case M_8BIT:
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->RSPin,HIGH); //set RS pin for send data
		GPIO_write_port(LCDOBj->DataPort,data);// send data at the port
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->EnPin,HIGH);	 //set enable pin high
		_delay_us(2);
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->EnPin,LOW);
		_delay_us(2);
		break;

		case M_4BIT_SAMEPORT:		
		GPIO_write_pin(LCDOBj->cmdport,0,HIGH); //Set RS pin High for send Data
		GPIO_write_port_mask_HN(LCDOBj->DataPort,data);	// Send high nibble from data  (GPIO_write_port_set_mask_High(ptr->port, Dta);)
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->EnPin,HIGH); //set Enable Pin High
		_delay_ms(2);
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->EnPin,LOW); //set Enable Pin Low
		_delay_ms(2);
		GPIO_write_port_mask_LN(LCDOBj->DataPort,data);	// Send Low nibble from data
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->EnPin,HIGH); //set Enable Pin High
		_delay_ms(2);
		GPIO_write_pin(LCDOBj->cmdport,LCDOBj->EnPin,LOW); //set Enable Pin Low
		_delay_ms(2);
		break;

		case M_4BIT_SEPARATED:

		break;
	}
}
 
 void LCD_WriteChar(uint8 character)
{
	LCD_SendData(character);
}

void LCD_WriteSentence(uint8 *PtrSentance)//"ahmed0"
{
	uint8 i=0;
	while(PtrSentance[i])
	{
		if(pos<=15)
		{		
		pos++;
		}
		else if(pos>15 && pos<=31)
		{
			  LCD_WriteCommand(Forc_2ST+(pos-15) );
			  pos++;
		}
		else
		{
			 LCD_WriteCommand(Clear_LCD);
			 LCD_WriteCommand(Return_Home);
			 pos=0;
			 break;
		}
		LCD_SendData(PtrSentance[i]);
		i++;
	}
}

void LCD_Clear(void)
{ 
	LCD_WriteCommand(0x01);
}

void LCD_GoTo(uint8 Line, uint8 x)// 0 1
{

	if(0 == Line)
	{
		if ( x <=15)
		{
			LCD_WriteCommand(Forc_1ST + x);
		}
	}
	else if (1 == Line)
	{
		if ( x <=15)
		{
			LCD_WriteCommand(Forc_2ST + x);
		}
	}
}

void LCD_WriteNumber(uint32 Number)
{
	uint8 i=0,arr[10],j;
	if(Number==0)
	LCD_SendData('0');
	else{
		while(Number)
		{
			arr[i]=Number%10+'0';
			Number/=10;
			i++;
		}
		for(j=i;j>0;j--)
		{
			LCD_SendData(arr[j-1]);
		}
	}
}

void LCD_WriteNumber2(uint16 Number)
{
	LCD_SendData(Number%10000/1000+'0');
	LCD_SendData(Number%1000/100+'0');
	LCD_SendData(Number%100/10+'0');
	LCD_SendData(Number%10/1+'0');
}

uint8 *convert_data(uint32 val)
{
	uint8 i=0;
	static uint8 arr[10]={0};
	if(val==0)
	{arr[i]='0';}
	else{
		while(val)//123
		{
			arr[8-i]=val%10+'0';
			val/=10;
			i++;
		}
	}
	return &arr[8-i+1];
}

uint32 str_to_int(uint8*ptr)
{
	uint32 number=0;
	for(uint16 i=0;i<strlen((char*)ptr);i++)
	{
		number=(ptr[i]-48)+number*10;
		
	}
	return number;
}

void Create_Character(uint8 *Pattern,uint8 Location) {

	uint8 iLoop=0;

	LCD_WriteCommand(0x40+(Location*8)); //Send the Address of CGRAM
	for(iLoop=0;iLoop<8;iLoop++)
	LCD_SendData(Pattern[iLoop]); //Pass the bytes of pattern on LCD

}

