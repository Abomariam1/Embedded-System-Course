/*
 * Timer.c
 *
 * Created: 13/03/2022 05:34:55 م
 *  Author: PC
 */ 
  #include "Timer.h"
  #include "../../MCAL_Registers/MEM_MapAvr328P.h"

  volatile uint16 t1,t2,t3,flag=0;
  static volatile uint8 scaler0_global=0;
  static volatile uint8 scaler1_global=0;
  /****************************Pointer to functions to be assigned to ISR*********************************/
  static void (*TIMER0_OVF_Fptr) (void)=NULLPTR;
  static void (*TIMER0_CMP_Fptr) (void)=NULLPTR;
  //static void (*Timer1_OVF_Fptr) (void)=NULLPTR;
  //static void (*Timer1_OCA_Fptr) (void)=NULLPTR;
  //static void (*Timer1_OCB_Fptr) (void)=NULLPTR;
  //static void (*Timer1_ICU_Fptr) (void)=NULLPTR;

  void TIMER0_Init( TIMER0_Mode_t mode,TIMER0_Prescalar scaler ,TIMER0_OC0A_Mode_tt oc_mode)
{
	/*
	Timer/Counter Control
	Register  TCCR0
	FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00
	
	 0 0 Normal 0xFF Immediate MAX
	 0 1 PWM, Phase Correct 0xFF TOP BOTTOM
	 1 0 CTC OCR0 Immediate MAX
	 1 1 Fast PWM 0xFF BOTTOM MAX
	*/
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
			CLEAR_BIT(TCCR0A,WGM00);
			CLEAR_BIT(TCCR0A,WGM01);
			CLEAR_BIT(TCCR0B,WGM02);
		break;
		case TIMER0_PHASECORRECT_MODE:
			SET_BIT(TCCR0A,WGM00);
			CLEAR_BIT(TCCR0A,WGM01);
			CLEAR_BIT(TCCR0B,WGM02);
		break;
		case TIMER0_CTC_MODE:
			CLEAR_BIT(TCCR0A,WGM00);
			SET_BIT(TCCR0A,WGM01);
			CLEAR_BIT(TCCR0B,WGM02);
		break;
		case TIMER0_FASTPWM_MODE:
			SET_BIT(TCCR0A,WGM00);
			SET_BIT(TCCR0A,WGM01);
			CLEAR_BIT(TCCR0B,WGM02);

		break;
	}
 	TIMER0_CONTROL_PRES_ADJ(scaler);
 	scaler0_global = scaler;
 	switch (oc_mode)
 	{
	 	case OC0A_DISCONNECTED:
	 	CLEAR_BIT(TCCR0A, COM0A0);
	 	CLEAR_BIT(TCCR0A, COM0A1);
	 	break;
	 	case OC0A_TOGGLE:
	 	SET_BIT(TCCR0A, COM0A0);
	 	CLEAR_BIT(TCCR0A, COM0A1);
	 	break;
	 	case OC0A_NON_INVERTING:
	 	CLEAR_BIT(TCCR0A, COM0A0);
	 	SET_BIT(TCCR0A, COM0A1);
	 	break;
	 	case OC0A_INVERTING:
	 	SET_BIT(TCCR0A, COM0A0);
	 	SET_BIT(TCCR0A, COM0A1);
	 	break;
 	}
 }
void TIMER0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK0, TOIE0);
}

void TIMER0_OV_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK0, TOIE0);
}

 // Timer/Counter0 Output Compare Match A Interrupt Enable
void TIMER0_OC0A_InterruptEnable(void)
{
	SET_BIT(TIMSK0, OCIE0A);
}

void TIMER0_OC0A_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK0, OCIE0A);
}

void TIMER0_OVF_SetCallBack(void (*LocalFptr)(void))
{
	TIMER0_OVF_Fptr = LocalFptr;
}

void TIMER0_CMP_SetCallBack(void (*LocalFptr)(void))
{
	TIMER0_CMP_Fptr = LocalFptr;
}

 void TIMER0_reload(uint8 TIMER0_val)
 {
	 TCNT0=TIMER0_val;
 }

 void TIMER0_Compare_reload(uint8 TIMER0_comp_val)
 {
	 OCR0A=TIMER0_comp_val;
 }

 uint8 Get_Current_Timer()
 {
	 return TCNT0;
 }
 void TIMER0_Stop()
 {
	 PORT_CLEAR_MASK(TCCR0B,TIM_STOP);
 }

 void TIMER0_restart(){

	 TCCR0B|=scaler0_global;
 }

 ISR(TIMER0_OVF_vect)
 {
	 if(TIMER0_OVF_Fptr!=NULLPTR)
	 {
		 TIMER0_OVF_Fptr();
	 }
 }