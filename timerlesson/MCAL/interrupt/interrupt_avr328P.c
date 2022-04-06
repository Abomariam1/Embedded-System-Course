/*
 * interrupt_avr328P.c
 *
 * Created: 26/03/2022 07:40:27 PM
 *  Author: PC
 */ 

 
 /************************************************************************/
 /*                      Interrupt Functions                             */
 /************************************************************************/
 #include "interrupt_avr328P.h"
 
 static void (*GPIO_int0_ptr)(void); /* to catch interrupt function address an pass it to ISR function. */
 static void (*GPIO_int1_ptr)(void); /* to catch interrupt function address an pass it to ISR function. */

 //------------------------------------------------------------------------------------------------------
 /********************************************************************
 * Func : init_pin
 * Args
 * GPIO_INPUT : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
 : pin -> pin number (0,1,2,3,4,5,6,7)
 : dir -> GPIO_INPUT
 -> GPIO_OUTPUT
 *Return : state -> it includes two possiblilities
 Success_Pass  = function success
 E_FAIL  = function fail
 **********************************************************************/
 static void init_GPIO_INT0_interrupt(GPIO_EXT_INTERRUPT_t *obj)
 {
	 GPIO_int0_ptr = obj->InterruptFunctionPtr; // local pointerto function ->fun//setcallback
	 SET_BIT(EIMSK, INT0);			   // Peripheral interrupt 0

	 if (obj->InterruptSenseControl == Low_Level_Of_Interrupt)
	 {
		 CLEAR_BIT(EICRA, ISC00);
		 CLEAR_BIT(EICRA, ISC01);
	 }
	 else if (obj->InterruptSenseControl == Any_Logical_Change_On_Interrupt)
	 {
		 SET_BIT(EICRA, ISC00);
		 CLEAR_BIT(EICRA, ISC01);
	 }
	 else if (obj->InterruptSenseControl == FallingEdge_On_Interrupt)
	 {
		 CLEAR_BIT(EICRA, ISC00);
		 SET_BIT(EICRA, ISC01);
	 }
	 else if (obj->InterruptSenseControl == RisingEdge_On_Interrupt)
	 {
		 SET_BIT(EICRA, ISC00);
		 SET_BIT(EICRA, ISC01);
	 }
	 
 }
 //-----------------------------------------------------------------------
 static void init_GPIO_INT1_interrupt(GPIO_EXT_INTERRUPT_t *obj)
 {

	 GPIO_int1_ptr = obj->InterruptFunctionPtr;
	 WRITE_BIT(EIMSK, INT1, HIGH);

	 if (obj->InterruptSenseControl == Low_Level_Of_Interrupt)
	 {
		 WRITE_BIT(EICRA, ISC10, LOW);
		 WRITE_BIT(EICRA, ISC11, LOW);
	 }
	 else if (obj->InterruptSenseControl == Any_Logical_Change_On_Interrupt)
	 {
		 WRITE_BIT(EICRA, ISC10, HIGH);
		 WRITE_BIT(EICRA, ISC11, LOW);
	 }
	 else if (obj->InterruptSenseControl == FallingEdge_On_Interrupt)
	 {
		 WRITE_BIT(EICRA, ISC10, LOW);
		 WRITE_BIT(EICRA, ISC11, HIGH);
	 }
	 else if (obj->InterruptSenseControl == RisingEdge_On_Interrupt)
	 {
		 WRITE_BIT(EICRA, ISC10, HIGH);
		 WRITE_BIT(EICRA, ISC11, HIGH);
	 }
 }
 //----------------------------------------------------------------------
 /* static void init_GPIO_INT2_interrupt(GPIO_interrupt_t *obj)
 {

 GPIO_int2_ptr = obj->interruptFunctionPtr; // localptr
 WRITE_BIT(GICR, PIN_5, HIGH);

 if (obj->interruptSenseControl == FALLING_EDGE_OF_INTERRUPT)
 {
 WRITE_BIT(MCUCSR, PIN_6, LOW);
 }
 else if (obj->interruptSenseControl == RISING_EDGE_OF_INTERRUPT)
 {
 WRITE_BIT(MCUCSR, PIN_6, HIGH);
 }
 } */
 //-----------------------------------------------------------------------

 void GPIO_init_interrupt(GPIO_EXT_INTERRUPT_t *obj)
 {

	 // sei();//global interrupt enable
	 if (obj->ExtInterruptSelectPin == EXT_Int0_PD2)
	 {
		 init_GPIO_INT0_interrupt(obj);
	 }
	 else if (obj->ExtInterruptSelectPin == EXT_Int1_PD3)
	 {
		 init_GPIO_INT1_interrupt(obj);
	 }
	 
 }
 //------------------------------------------
 ISR(INT0_vect)
 {

	 GPIO_int0_ptr();
 }
 //-------------------------------------
 ISR(INT1_vect)
 {
	 (*GPIO_int1_ptr)();
 }
 //-----------------------------------
 /* ISR(INT2_vect)
 {
 (*GPIO_int2_ptr)();
 } */
