#if !defined(GPIO_AVR328P_H)
#define GPIO_AVR328P_H
#include "../../Helpers/Std_Types.h"
#include "../../Helpers/Utils.h"
#include "../../MCAL_Registers/MEM_MapAvr328P.h"

#define MAX_PINS 7

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

#define GPIO_HIGH 1
#define GPIO_LOW 0

#define GPIO_PORT_INPUT 0xff
#define GPIO_PORT_OUTPUT 0x00

#define PULLUP 1
#define PULLDOWN 0

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

/*
 * enum for check if function return  1 = success
 */

typedef enum
{
    GPIO_B,
    GPIO_C,
    GPIO_D
} GPIO_port_name_t;


/*
 * enum for check if function return  1 = success
 */
typedef enum
{
    Success_Pass = 1,
    Faild_Pass
} GPIO_error_t;

typedef struct
{
    GPIO_port_name_t port_name;
    uint8 pin_select[8];
    uint8 pin_direction[8];
    uint8 pin_res_type[8];
} GPIO_config_t;


GPIO_error_t GPIO_init_pin(uint8 reg, uint8 pin, uint8 dir);
void GPIO_init_port(uint8 reg, uint8 val);
void GPIO_init_port_mask(uint8 reg, uint8 val);

GPIO_error_t GPIO_write_pin(uint8 reg, uint8 pin, uint8 val);
void GPIO_write_port(uint8 reg, uint8 val);
void GPIO_write_port_set_mask(uint8 reg, uint8 val);
void GPIO_write_port_clear_mask(uint8 reg, uint8 val);
void GPIO_write_port_mask(uint8 reg, uint8 setval, uint8 clearval);
GPIO_error_t GPIO_read_pin_argument(uint8 reg, uint8 pin, uint8 *data);
GPIO_error_t GPIO_read_port_argument(uint8 reg, uint8 *val);
uint8 GPIO_read_pin(uint8 reg, uint8 pin);
uint8 GPIO_read_port(uint8 reg);

GPIO_error_t GPIO_set_pullup(uint8 reg, uint8 pin);
GPIO_error_t GPIO_set_pulldown(uint8 reg, uint8 pin);
void GPIO_set_gpiopad(GPIO_config_t GPIO_pad);   // struct
void GPIO_Send_HigherNibble(uint8 Reg,uint8 Data);
void GPIO_Send_LowerNibble(uint8 Reg,uint8 Data);


#endif // GPIO_AVR328P_H
