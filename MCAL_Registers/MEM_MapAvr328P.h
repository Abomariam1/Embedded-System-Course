/*
Mostafa Osman
*/
#if !defined(_H_MEM_MAPAVR328P)
#define _H_MEM_MAPAVR328P

//**************************************************************
#define UDR0    (*((volatile unsigned char *)0xC6))
#define UBRR0H  (*((volatile unsigned char *)0xC5))
#define UBRR0L  (*((volatile unsigned char *)0xC4))
#define UCSR0C  (*((volatile unsigned char *)0xC2))
#define UCSR0B  (*((volatile unsigned char *)0xC1))
#define UCSR0A  (*((volatile unsigned char *)0xC0))
#define TWAMR   (*((volatile unsigned char *)0xBD))
#define TWCR    (*((volatile unsigned char *)0xBC))
#define TWDR    (*((volatile unsigned char *)0xBD))
#define TWAR    (*((volatile unsigned char *)0xBA))
#define TWSR    (*((volatile unsigned char *)0xB9))
#define TWBR    (*((volatile unsigned char *)0xB8))
#define ASSR    (*((volatile unsigned char *)0xB6))
#define OCR2B   (*((volatile unsigned char *)0xB4))
#define OCR2A   (*((volatile unsigned char *)0xB3))
#define TCNT2   (*((volatile unsigned char *)0xB2))
#define TCCR2B  (*((volatile unsigned char *)0xB1))
#define TCCR2A  (*((volatile unsigned char *)0xB0))
#define OCR1BH  (*((volatile unsigned char *)0x8B))
#define OCR1BL  (*((volatile unsigned char *)0x8A))
#define OCR1AH  (*((volatile unsigned char *)0x89))
#define OCR1AL  (*((volatile unsigned char *)0x88))
#define ICR1H   (*((volatile unsigned char *)0x87))
#define ICR1L   (*((volatile unsigned char *)0x86))
#define TCNT1H  (*((volatile unsigned char *)0x85))
#define TCNT1L  (*((volatile unsigned char *)0x84))
#define TCCR1C  (*((volatile unsigned char *)0x82))
#define TCCR1B  (*((volatile unsigned char *)0x81))
#define TCCR1A  (*((volatile unsigned char *)0x80))
#define DIDR1   (*((volatile unsigned char *)0x7F))
#define DIDR0   (*((volatile unsigned char *)0x7E))

#define ADCSRB  (*((volatile unsigned char *)0x7B))

#define ADCH    (*((volatile unsigned char *)0x79))
#define ADCL    (*((volatile unsigned char *)0x78))
#define TIMSK2  (*((volatile unsigned char *)0x70))
#define TIMSK1  (*((volatile unsigned char *)0x6F))
#define TIMSK0  (*((volatile unsigned char *)0x6E))
#define PCMSK2  (*((volatile unsigned char *)0x6D))
#define PCMSK1  (*((volatile unsigned char *)0x6C))
#define PCMSK0  (*((volatile unsigned char *)0x6B))

#define OSCCAL  (*((volatile unsigned char *)0x66))
#define PRR     (*((volatile unsigned char *)0x64))
#define CLKPR   (*((volatile unsigned char *)0x61))
#define SREG    (*((volatile unsigned char *)0x5F)) // Status Register
#define SPH     (*((volatile unsigned char *)0x5E))
#define SPL     (*((volatile unsigned char *)0x5D))
#define SPMCSR  (*((volatile unsigned char *)0x57))

#define MCUSR   (*((volatile unsigned char *)0x54))
#define SMCR    (*((volatile unsigned char *)0x53))
#define ACSR    (*((volatile unsigned char *)0x50))
#define SPDR    (*((volatile unsigned char *)0x4E))
#define SPSR    (*((volatile unsigned char *)0x4D))
#define SPCR    (*((volatile unsigned char *)0x4C))
#define GPIOR2  (*((volatile unsigned char *)0x4B))
#define GPIOR1  (*((volatile unsigned char *)0x4A))
#define OCR0B   (*((volatile unsigned char *)0x48))
#define OCR0A   (*((volatile unsigned char *)0x47))
#define TCNT0   (*((volatile unsigned char *)0x46))
#define TCCR0B  (*((volatile unsigned char *)0x45))
#define TCCR0A  (*((volatile unsigned char *)0x44))
#define GTCCR   (*((volatile unsigned char *)0x43))
#define EEARH   (*((volatile unsigned char *)0x42))
#define EEARL   (*((volatile unsigned char *)0x41))
#define EEDR    (*((volatile unsigned char *)0x40))
#define EECR    (*((volatile unsigned char *)0x3F))
#define GPIOR0  (*((volatile unsigned char *)0x3E))

#define PCIFR   (*((volatile unsigned char *)0x3B))
#define TIFR2   (*((volatile unsigned char *)0x37))
#define TIFR1   (*((volatile unsigned char *)0x36))
#define TIFR0   (*((volatile unsigned char *)0x35))
#define PORTD   (*((volatile unsigned char *)0x2B))
#define DDRD    (*((volatile unsigned char *)0x2A))
#define PIND    (*((volatile unsigned char *)0x29))
#define PORTC   (*((volatile unsigned char *)0x28))
#define DDRC    (*((volatile unsigned char *)0x27))
#define PINC    (*((volatile unsigned char *)0x26))
#define PORTB   (*((volatile unsigned char *)0x25))
#define DDRB    (*((volatile unsigned char *)0x24))
#define PINB    (*((volatile unsigned char *)0x23))



/* ADC_Registers */
//****************************************************
#define ADMUX   (*((volatile unsigned char *)0x7C))
#define ADLAR 5
#define REFS0 6
#define REFS1 7
//*********************************************************
#define ADCSRA  (*((volatile unsigned char *)0x7A))
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE 3
#define ADIF 4
#define ADATE 5
#define ADSC 6
#define ADEN 7

//***********************************************************
/* Interrupt */

// MCU Control Register
#define MCUCR   (*((volatile unsigned char *)0x55))

#define BODS 6  // Bit 6 – BODS: BOD Sleep
#define BODSE 5 // Bit 5 – BODSE: BOD Sleep Enable
#define PUD 4 // Bit 4 – Pull-up Disable
#define IVSEL 1 // Interrupt Vector Select
#define IVCE 0  // Interrupt Vector Change Enable

// External Interrupt Control Register A
#define EICRA   (*((volatile unsigned char *)0x69))

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

// External Interrupt Mask Register
#define EIMSK   (*((volatile unsigned char *)0x3D))
#define INT0 0
#define INT1 1

// External Interrupt Flag Register
#define EIFR    (*((volatile unsigned char *)0x3C))
#define INTF0 0
#define INTF1 01

// Pin Change Interrupt Control Register
#define PCICR   (*((volatile unsigned char *)0x68))

/* Interrupt vectors */
/* External Interrupt Request 0 */
#define INT0_vect __vector_2

/* External Interrupt Request 1 */
#define INT1_vect __vector_3

/* Pin Change Interrupt Request 0 */
#define PCINT0_vect __vector_4

/* Pin Change Interrupt Request 1 */
#define PCINT1_vect __vector_5

/* Pin Change Interrupt Request 2 */
#define PCINT2_vect __vector_6

/* Watchdog Time-out Interrupt */
#define WDT_vect __vector_7

/* Timer/Counter2 Compare Match A */
#define TIMER2_COMPA_vect __vector_8

/* Timer/Counter2 Compare Match B */
#define TIMER2_COMPB_vect __vector_9

/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect __vector_10

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect __vector_11

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect __vector_12

/* Timer/Coutner1 Compare Match B */
#define TIMER1_COMPB_vect __vector_13

/* Timer/Counter1 Overflow*/
#define TIMER1_OVF_vect __vector_14

/* Timer/Counter0 Compare Match A */
#define TIMER0_COMPA_vect __vector_15

/* Timer/Counter0 Compare Match B */
#define TIMER0_COMPB_vect __vector_16

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect __vector_17

/* SPI Serial Transfer Complete */
#define SPI_STC_vect __vector_18

/* USART Rx Complete */
#define USART_RX_vect __vector_19

/* USART, Data Register Empty*/
#define USART_UDRE_vect __vector_20

/* USART, Tx Complete */
#define USART_TX_vect __vector_21

/* ADC Conversion Complete */
#define ADC_vect __vector_22

/* EEPROM Ready */
#define EE_READY_vect __vector_23

/* Analog Comparator */
#define ANALOG_COMP_vect __vector_24

/* 2-wire Serial Interface */
#define TW_vect __vector_25

/* Store Program Memory Ready */
#define SPM_READY_vect __vector_26

/*interrupt functions*/

#define sei() __asm__ __volatile__("sei" ::)
#define cli() __asm__ __volatile__("cli" ::)
#define reti() __asm__ __volatile__("reti" ::)

#define ISR_NOBLOCK __attribute__((interrupt))
#define ISR_NAKED __attribute__((naked))

#define ISR(vector, ...)                                   \
    void vector(void) __attribute__((signal)) __VA_ARGS__; \
    void vector(void)

#endif // _H_MEM_MAPAVR328P
