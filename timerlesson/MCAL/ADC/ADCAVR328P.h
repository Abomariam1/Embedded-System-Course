/*
 * ADCAVR328P.h
 *
 * Created: 27/03/2022 09:38:44 PM
 *  Author: PC
 */ 


#ifndef ADCAVR328P_H_
#define ADCAVR328P_H_

#include "../../Helpers/Std_Types.h"
#include "../../Helpers/Utils.h"
#include "../../MCAL_Registers/MEM_MapAvr328P.h"

typedef enum 
{
	AREF,
	AVcc,
	INTERNAL1V1=3	
}ADC_VREF_t;

typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	Vbg=14,
	GND
}ADC_INPUT_CHANEL_t;
typedef enum 
{
	FACTOR_2=1,
	FACTOR_4,
	FACTOR_8,
	FACTOR_16,
	FACTOR_32,
	FACTOR_64,
	FACTOR_128	
}ADC_PRESCALER_t;

typedef enum
{
	ADC_AT_DISABLE,
	FREE_RUNNIN_MODE,
	ANALOG_COMPARATOR,
	EXTINT0,
	TIMER0COMPAREA,
	TIMER0OVF,
	TIMER1COMPAREB,
	TIMER1OVF,
	TIMER1CAPTCHER
}ADC_ATrigger_Selections_t;

typedef enum
{
ADC_ADLER_RIGHT,
ADC_ADLER_Left
}ADC_ADLER_t;

typedef enum
{
	EnableInterrupt,
	DisableInterrupt
}ADC_INTERRUPT_Stats_t;

typedef struct
{
	ADC_VREF_t 	ADC_VREF;
	ADC_INPUT_CHANEL_t ADC_INPUT_CHANEL;
	ADC_PRESCALER_t ADC_PRESCALER;
	ADC_ATrigger_Selections_t ADC_ATrigger_Selections;
	ADC_ADLER_t ADC_ADLER;
	ADC_INTERRUPT_Stats_t ADC_INTERRUPT_Stats;
}ADC_CONFIG_t;

/***********************************************/

void ADC_Init(ADC_CONFIG_t *ADCObject);
uint16 ADC_READ(void);
void ADC_ChangePrescaler(ADC_PRESCALER_t ADC_PRESCAL);
void ADC_ChangeVREFRANCE(ADC_VREF_t ADC_VREFRANCE);
void ADC_ChangeADC_CHANEL(ADC_PRESCALER_t ADC_CHANEL);
void ADC_ChangeATrigger(ADC_ATrigger_Selections_t ATrigger);
void ADC_Enable();
void ADC_Disable();
void ADC_StarConvetion();
uint16 Get_ADCRegister();
uint8 Get_ADCInterruptFlage();
void ADC_InitInterrupt(void(*ADC_InterruptFunctinPTR)(void));

#endif /* ADCAVR328P_H_ */