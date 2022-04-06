/*
* interrupt_avr328P.h
*
* Created: 26/03/2022 07:42:03 PM
*  Author: PC
*/


#ifndef INTERRUPT_AVR328P_H_
#define INTERRUPT_AVR328P_H_
#include "../../Helpers/Std_Types.h"
#include "../../Helpers/Utils.h"
#include "../../MCAL_Registers/MEM_MapAvr328P.h"

/*
* enum for external interrupt physical pin
*/
typedef enum
{
	EXT_Int0_PD2 = 1,
	EXT_Int1_PD3
} GPIO_INTPIN_t;

/*
* enum for interrupt sense control mode
*/
typedef enum
{
	Low_Level_Of_Interrupt = 1,
	Any_Logical_Change_On_Interrupt,
	FallingEdge_On_Interrupt,
	RisingEdge_On_Interrupt
} GPIO_INTERRUPT_SENSE_CONTROL_t;

/*
* Struct for External interrupt
*/

typedef struct
{
	GPIO_INTPIN_t  ExtInterruptSelectPin;
	GPIO_INTERRUPT_SENSE_CONTROL_t  InterruptSenseControl;
	void (*InterruptFunctionPtr)(void);
} GPIO_EXT_INTERRUPT_t;


 void GPIO_init_interrupt(GPIO_EXT_INTERRUPT_t *obj); // ptrtostruct



#endif /* INTERRUPT_AVR328P_H_ */