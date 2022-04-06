/*
* timerlesson.c
*
* Created: 01/03/2022 04:59:55 م
* Author : PC
*/

#include <avr/delay.h>
#include "Helpers/Std_Types.h"
#include "Helpers/Utils.h"
#include "MCAL/GPIO/GPIO_AVR328P.h"
#include "MCAL_Registers/MEM_MapAVR328P.h"
#include "MCAL/Timer/Timer.h"
#include "HAL/LCD/LCDLM016L.h"
#include "MCAL/interrupt/interrupt_avr328P.h"
#include "MCAL/ADC/ADCAVR328P.h"
#define F_CPU 16000000UL
GPIO_EXT_INTERRUPT_t button_interrupt;
LcdInit_t LCDObj;
ADC_CONFIG_t ADCInitObject;

void led_Blinking()
{
	TOG_BIT(PORTC,PIN_5);
}

void Timer_interrupt()
{
	static uint16 Counter0 = 0;
	Counter0++;
	TCNT0 = 5;
	if (Counter0 >= 1000){
		TOG_BIT(PORTC,PIN_5);
		Counter0 = 0;
	}

}

int main ()
{
	
	//WRITE_BIT(DDRC,PIN_5,GPIO_OUTPUT);
	//SET_BIT(PORTC,PIN_5);
	//WRITE_BIT(DDRD,PIN_2,GPIO_INPUT); // make port d pin2 as input
	//GPIO_set_pullup(GPIO_D,PIN_2); // make pin 2 pull up mode active
	//button_interrupt.ExtInterruptSelectPin = EXT_Int0_PD2;
	//button_interrupt.InterruptSenseControl = FallingEdge_On_Interrupt;
	//button_interrupt.InterruptFunctionPtr = led_Blinking;
	//GPIO_init_interrupt(&button_interrupt);
	//TCNT0 = 5;
	//TIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_64,OC0A_DISCONNECTED);
	///*
	//F=16M------ prescaler = 8 --------- time for 1 pulse = 0.5us		TOVF = 256 * 0.5 = 	128us
	//F=16M------ prescaler = 64 --------- time for 1 pulse = 4us		TOVF = 256 * 4   = 	1024us
	//F=16M------ prescaler = 256 --------- time for 1 pulse = 16us		TOVF = 256 * 16  = 	4096us
	//F=16M------ prescaler = 1024 --------- time for 1 pulse = 64us		TOVF = 256 * 64  = 	16384us
	//
	//*/
	//TIMER0_OV_InterruptEnable();
	//TIMER0_OVF_SetCallBack(Timer_interrupt);
	//
	//
	//WRITE_BIT(SREG,PIN_7,HIGH);
	/* button_interrupt.interruptBtn_CallbackctionPtr=Btn_Callback;//set Btn_Callbackction to callback Btn_Callbackction
	button_interrupt.interruptPinSelect=EXT_INTERRPUT_INT0_PD2 ;//select external interrupt pin
	button_interrupt.interruptSenseControl=FALLING_EDGE_OF_INTERRUPT;//select type of edge detector
	GPIO_init_inte rrupt(&button_interrupt);//call init Btn_Callbackction to prepared interrupt to use
	*/
	LCDObj.Mode = M_4BIT_SAMEPORT;
	LCDObj.DataPort = GPIO_D;
	LCDObj.cmdport= GPIO_D;
	LCDObj.RSPin = 0;
	LCDObj.EnPin = 1;
	LCDObj.PortVal = 0xF3;
	Lcd_Init(&LCDObj);
	
	ADCInitObject.ADC_ADLER = ADC_ADLER_RIGHT;
	ADCInitObject.ADC_ATrigger_Selections = ADC_AT_DISABLE;
	ADCInitObject.ADC_INPUT_CHANEL = ADC0;
	ADCInitObject.ADC_PRESCALER = FACTOR_8;
	ADCInitObject.ADC_VREF = AREF;
	ADCInitObject.ADC_INTERRUPT_Stats = DisableInterrupt;
	ADC_Init(&ADCInitObject);
	uint16 u16AdcRecev=0,u16old_val=0;
	uint8 flag = 0;
	char arr[]="2015Mariam";
	//char arr2[]="Mostafa Osman";
	while(1)
	{
		//while (arr[i])
		//{//
			//LCD_WriteChar(arr[i]);
			//i++;
		//}
		flag = GET_BIT(ADCSRA,ADIF);
		u16AdcRecev=Get_ADCRegister();
		 
		if (flag)
		{
			LCD_WriteChar('1') ;
		}
		else
		{
			LCD_WriteChar('0') ;
		}
		_delay_ms(600);
		if(u16AdcRecev!=u16old_val)
		{
			cli(); //critical section protection
			LCD_Clear();
			LCD_GoTo(0, 0);
			u16old_val = u16AdcRecev;
			LCD_WriteNumber2((uint16)u16AdcRecev);
			sei();//critical section protection
		}
		LCD_Clear();
		LCD_WriteNumber2((uint16)u16AdcRecev);
		_delay_ms(600);
		LCD_Clear();
		
		//while (arr2[H])
		//{//
			//LCD_WriteChar(arr2[H]);
			//H++;
		//}
		//_delay_ms(500);

	}

	return 0;
}

/*

*/