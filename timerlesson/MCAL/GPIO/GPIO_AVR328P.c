#include "GPIO_AVR328P.h"
#include "../../Helpers/Std_Types.h"
#include "../../Helpers/Utils.h"
#include "../../MCAL_Registers/MEM_MapAvr328P.h"

volatile uint8 *register_Dir[3]={&DDRB,&DDRC,&DDRD};
volatile uint8 *register_Port[3]={&PORTB,&PORTC,&PORTD};
volatile uint8 *register_PIN[3]={&PINB,&PINC,&PIND};

GPIO_error_t GPIO_init_pin(uint8 reg, uint8 pin, uint8 dir)
{
	GPIO_error_t state = Success_Pass;
	if((dir == GPIO_OUTPUT || dir == GPIO_INPUT)&& pin <= MAX_PINS && reg <= 2){
		WRITE_BIT(*register_Dir[reg],pin,dir);
	}
	else
	{
		state = Faild_Pass;
	}
	return state;
}

//------------------------------------------------------------------
/*********************************************************
* Func : init_port
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
: dir -> PORT_INPUT
-> PORT_OUTPUT
example:
GPIO_init_port(GPIO_A,0x0f);
DDRA |=0x0f; 0bxxxx 1111
************************************************************/

void GPIO_init_port(uint8 reg, uint8 val)
{
	WRITE_PORT(*register_Dir[reg], val);
}

void GPIO_init_port_mask(uint8 reg, uint8 val)
{
	PORT_SET_MASK(*register_Dir[reg], val);
}


//------------------------------------------------------------------
/**
* Func : write_pin
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
: pin -> pin number (0,1,2,3,4,5,6,or 7)
: val -> HIGH
-> LOW
*Return : state -> it includes two possiblilities
Success_Pass  = function success
E_FAIL  = function fail
*/
GPIO_error_t GPIO_write_pin(uint8 reg, uint8 pin, uint8 val){
	GPIO_error_t state = Success_Pass;
	if ((HIGH == val || (LOW == val)) && (pin <= MAX_PINS) && reg <=2)
	{
		WRITE_BIT(*register_Port[reg], pin, val);
	}
	else
	{
		state = Faild_Pass;
	}

	return state;
}

//------------------------------------------------------------------
/**
* Func : write_port
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
: val -> PORT_HIGH
-> PORT_LOW
*/
void GPIO_write_port(uint8 reg, uint8 val)
{
	WRITE_PORT(*register_Port[reg], val);
}
void GPIO_write_port_set_mask(uint8 reg, uint8 val)
{
	PORT_SET_MASK(*register_Port[reg], val);
}
void GPIO_write_port_clear_mask(uint8 reg, uint8 val)
{
	PORT_CLEAR_MASK(*register_Port[reg], val);
}

void GPIO_write_port_mask(uint8 reg, uint8 setval, uint8 clearval)
{
	PORT_MASK(*register_Port[reg], setval, clearval);
}

void GPIO_write_port_mask_HN(uint8 reg, uint8 VAL)
{
	HIGHER_NIBBLE_CLEAR_REG(*register_Port[reg]);
	HNDATA_HNREG(*register_Port[reg], VAL);
}

void GPIO_write_port_mask_LN(uint8 reg, uint8 VAL)
{
	HIGHER_NIBBLE_CLEAR_REG(*register_Port[reg]);
	LNDATA_HNREG(*register_Port[reg], VAL);
}
//------------------------------------------------------------------
/**
* Func : read_pin
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
: pin -> pin number (0,1,2,3,4,5,6,or 7)
: *data->pointer to return the value in
*Return : state -> it includes two possiblilities
Success_Pass  = function success
E_FAIL  = function fail
GPIO_read_pin_argument(GPIO_A,2,&x);
*/
GPIO_error_t GPIO_read_pin_argument(uint8 reg, uint8 pin, uint8 *data)
{
	GPIO_error_t state = Success_Pass;
	if ((pin <= MAX_PINS))
	{
		*data = GET_BIT(*register_PIN[reg], pin);
	}
	else
	{
		state = Faild_Pass;
	}
	return state;
}

uint8 GPIO_read_pin(uint8 reg, uint8 pin)
{
	return GET_BIT(*register_PIN[reg], pin);
}
//----------------------------------------------------------------
/**
* Func : read_port
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
: pin -> pin number (0,1,2,3,4,5,6,or 7)
: *val ->pointer to return the value in
*/
GPIO_error_t GPIO_read_port_argument(uint8 reg, uint8 *val)
{
	GPIO_error_t status = Success_Pass;
	if (reg < 3)
	{
		*val = ReadPort(*register_PIN[reg]);
	}
	else
	{
		status = Faild_Pass;
	}
	return status;
}
uint8 GPIO_read_port(uint8 reg)
{
	return (ReadPort(*register_PIN[reg]));
}

GPIO_error_t GPIO_set_pullup(uint8 reg, uint8 pin)
{
	GPIO_error_t state = Success_Pass;
	if ((pin <= MAX_PINS) && (pin >= 0))
	{
		WRITE_BIT(*register_Port[reg], pin, GPIO_HIGH);
	}
	else
	{
		state = Faild_Pass;
	}
	return state;
}
GPIO_error_t GPIO_set_pulldown(uint8 reg, uint8 pin)
{
	GPIO_error_t state = Success_Pass;
	if ((pin <= MAX_PINS) && (pin >= 0))
	{
		WRITE_BIT(*register_Port[reg], pin, LOW);
	}
	else
	{
		state = Faild_Pass;
	}
	return state;
}

// Need to explain
void GPIO_set_gpiopad(GPIO_config_t GPIO_pad)
{
	for (uint8 index = 0; index <= MAX_PINS; index++)
	{
		if (GPIO_pad.pin_select[index] == 1)
		{
			GPIO_init_pin(GPIO_pad.port_name, index, GPIO_pad.pin_direction[index]);
			if (GPIO_pad.pin_res_type[index] == 1)
			{
				GPIO_set_pullup(GPIO_pad.port_name, index);
			}
			else
			{
				GPIO_set_pulldown(GPIO_pad.port_name, index);
			}
		}
	}
}

void GPIO_Send_HigherNibble(uint8 Reg,uint8 Data)
{
	HEIGHCMDREG(*register_Port[Reg], Data);
}

void GPIO_Send_LowerNibble(uint8 Reg,uint8 Data)
{
	LOWER_NIBBLE_VALUE(*register_Port[Reg], Data);
}
