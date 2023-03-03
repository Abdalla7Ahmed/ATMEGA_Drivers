/*
 * Timer.c
 *
 * Created: 09/02/2023 04:05:54 م
 *  Author: Abotaleb
 */ 

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Includes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "Includes/Timer8bit.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Macros
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define Normal_Mode_Index									0
#define CTC_Mode_Index										1
#define PWM_Mode_Index										2
#define Fast_PWM_Mode_Index									3

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Variables
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

DIO_PinConfig_t DIO_Pin;
Timer8bit_config_t Timer8bit_Mode[4] = {0};
void(* Timer0_IRQ_Compare_value_CallBack)(void);
void(* Timer0_IRQ_OverFlow_CallBack)(void);
void(* Timer2_IRQ_Compare_value_CallBack)(void);
void(* Timer2_IRQ_OverFlow_CallBack)(void);
uint32_t Timer0_Oveflow_Times =0;
uint32_t Timer2_Oveflow_Times =0;
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Functions
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
 void MCAL_Timer8bit_Init_Normal_Mode()
 {
	 uint8_t tempTCCR =0;
	  /*
	 COM1	COM0		Description
	 0		0			Normal port operation, OC disconnected.
	 0		1			Toggle OC on compare match
	 1		0			Clear OC on compare match
	 1		1			Set OC on compare match
	 */
	 switch(Timer8bit_Mode[Normal_Mode_Index].OC_Actio)
	 {
		 case OC_disconnected:
			 tempTCCR |= OC_disconnected;
			 break;
		 case Toggle_OC_on_compare_match:
			 tempTCCR |= Toggle_OC_on_compare_match;
			 break;
		 case Clear_OC_on_compare_match:
			tempTCCR |= Clear_OC_on_compare_match;
			 break;
		 case Set_OC_on_compare_match:
			 tempTCCR |= Set_OC_on_compare_match;
			 break;
	 } 
	 if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_ZERO)
	 {
		 _TCCR0 |=tempTCCR;
		 if(Timer8bit_Mode[Normal_Mode_Index].Interrupt_controle ==Timer0_Interrupt_Enable_Overflow)
		 {
			 // Enable the interrupt
			 _SREG |= (1<<7);
			 Timer0_IRQ_OverFlow_CallBack=Timer8bit_Mode[Normal_Mode_Index].P_OverFlow_IRQ_Callback;
			 Timer0_Enable_OverFlow_Interrupt();
		 }
		 else if (Timer8bit_Mode[Normal_Mode_Index].Polling_controle == Timer0_Polling_Enable_Overflow)
		 {
			 while(!(_TIFR & (Timer8bit_Mode[Normal_Mode_Index].Polling_controle)));
		 }
	 }
	 else if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_TWO)
	 {
		 _TCCR2 |=tempTCCR;
		 if(Timer8bit_Mode[Normal_Mode_Index].Interrupt_controle ==Timer2_Interrupt_Enable_Overflow)
		 {
			 // Enable the interrupt
			 _SREG |= (1<<7);
			 Timer2_IRQ_OverFlow_CallBack=Timer8bit_Mode[Normal_Mode_Index].P_OverFlow_IRQ_Callback;
			 Timer2_Enable_OverFlow_Interrupt();
		 }
		 else if (Timer8bit_Mode[Normal_Mode_Index].Polling_controle == Timer2_Polling_Enable_Overflow)
		 {
			 while(!(_TIFR & (Timer8bit_Mode[Normal_Mode_Index].Polling_controle)));
		 }
	 }
	 
	// the counter value
	MCAL_Timer8bit_UPdate_Counter(Timer8bit_Mode[Normal_Mode_Index].Timer8bit_Counter_Register_Value);
 }

// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=

void MCAL_Timer8bit_Init_CTC_Mode()
{
	uint8_t tempTCCR =0;
	 /*
	 COM1	COM0		Description
	 0		0			Normal port operation, OC disconnected.
	 0		1			Toggle OC on compare match
	 1		0			Clear OC on compare match
	 1		1			Set OC on compare match
	 */
	 switch(Timer8bit_Mode[CTC_Mode_Index].OC_Actio)
	 {
		 case OC_disconnected:
			 tempTCCR |= OC_disconnected;
			 break;
		 case Toggle_OC_on_compare_match:
			 tempTCCR |= Toggle_OC_on_compare_match;
			 break;
		 case Clear_OC_on_compare_match:
			tempTCCR |= Clear_OC_on_compare_match;
			 break;
		 case Set_OC_on_compare_match:
			 tempTCCR |= Set_OC_on_compare_match;
			 break;
	 } 
	 if(Timer8bit_Mode[CTC_Mode_Index].Timer_Number == Timer_Number_ZERO)
	 {
		 _TCCR0 |=tempTCCR;
		 if(Timer8bit_Mode[CTC_Mode_Index].Interrupt_controle ==Timer0_Interrupt_Enable_Compare)
		 {
			 // Enable the interrupt
			 _SREG |= (1<<7);
			 Timer0_IRQ_Compare_value_CallBack=Timer8bit_Mode[CTC_Mode_Index].P_Compare_IRQ_Callback;
			 Timer0_Enable_Compare_Interrupt();
		 }
		 else if (Timer8bit_Mode[CTC_Mode_Index].Polling_controle == Timer0_Polling_Enable_Compare)
		 {
			 while(!(_TIFR & (Timer8bit_Mode[CTC_Mode_Index].Polling_controle)));
		 }
		
	 }
	 else if(Timer8bit_Mode[CTC_Mode_Index].Timer_Number == Timer_Number_TWO)
	 {
		 _TCCR2 |=tempTCCR;
		 if(Timer8bit_Mode[CTC_Mode_Index].Interrupt_controle ==Timer2_Interrupt_Enable_Compare)
		 {
			 // Enable the interrupt
			 _SREG |= (1<<7);
			 Timer2_IRQ_Compare_value_CallBack=Timer8bit_Mode[CTC_Mode_Index].P_Compare_IRQ_Callback;
			 Timer2_Enable_Compare_Interrupt();
		 }
		 else if (Timer8bit_Mode[CTC_Mode_Index].Polling_controle == Timer2_Polling_Enable_Compare)
		 {
			 while(!(_TIFR & (Timer8bit_Mode[CTC_Mode_Index].Polling_controle)));
		 }
		
	 }
	 // the compare value
	 MCAL_Timer8bit_UPdate_Compair(Timer8bit_Mode[CTC_Mode_Index].Output_Compare_Register_Value);
}
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=

 void MCAL_Timer8bit_Init_PWM_Mode()
 {
	 uint8_t tempTCCR =0;
	 /*
	 COM1	COM0		Description
	 0		0			Normal port operation, OC disconnected.
	 0		1			Reserved
	 1		0			Clear OC on compare match when up-counting. Set OC on compare match when down counting.
	 1		1			Set OC on compare match when up-counting. Clear OC on compare match when down counting.
	 */
	 switch(Timer8bit_Mode[PWM_Mode_Index].OC_Actio)
	 {
		 case OC_disconnected:
			tempTCCR |= OC_disconnected;
			 break;
		 case Clear_OC_on_compareUP_set_OC_at_compareDown:
			 tempTCCR |= Clear_OC_on_compareUP_set_OC_at_compareDown;
			 break;
		 case Set_OC_on_compareUP_Clear_OC_at_compareDown:
			 tempTCCR |= Set_OC_on_compareUP_Clear_OC_at_compareDown;
			 break;
	 }
	 if(Timer8bit_Mode[PWM_Mode_Index].Timer_Number == Timer_Number_ZERO)
	 {
		 _TCCR0 |=tempTCCR;
	 }
	 else if(Timer8bit_Mode[PWM_Mode_Index].Timer_Number == Timer_Number_TWO)
	 {
		 _TCCR2 |=tempTCCR;
	 }
	 
	 // the compare value
	 MCAL_Timer8bit_UPdate_Compair(Timer8bit_Mode[PWM_Mode_Index].Output_Compare_Register_Value);
	  
 }
 // =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
 // =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
 // =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
 
 void MCAL_Timer8bit_Init_Fast_PWM_Mode()
 {
	 uint8_t tempTCCR =0;
	 /*
	 COM01	COM00		Description
	 0		0			Normal port operation, OC disconnected.
	 0		1			Reserved
	 1		0			Clear OC on compare match, set OC at BOTTOM, (nin-inverting mode)
	 1		1			Set OC on compare match, clear OC at BOTTOM, (inverting mode)
	 */
	 switch(Timer8bit_Mode[Fast_PWM_Mode_Index].OC_Actio)
	 {
		 case OC_disconnected:
			 tempTCCR |= OC_disconnected;
			 break;
		case Clear_OC_on_compare_set_OC_at_BOTTOM:
			tempTCCR |= Clear_OC_on_compare_set_OC_at_BOTTOM;
			break;
		case Set_OC_on_compare_Clear_OC_at_BOTTOM:
			tempTCCR |= Set_OC_on_compare_Clear_OC_at_BOTTOM;
			break;
	 }
	 if(Timer8bit_Mode[Fast_PWM_Mode_Index].Timer_Number == Timer_Number_ZERO)
	 {
		 _TCCR0 |=tempTCCR;
	 }
	 else if(Timer8bit_Mode[Fast_PWM_Mode_Index].Timer_Number == Timer_Number_TWO)
	 {
		 _TCCR2 |=tempTCCR;
	 }
	 
	 // the compare value
	 MCAL_Timer8bit_UPdate_Compair(Timer8bit_Mode[Fast_PWM_Mode_Index].Output_Compare_Register_Value);
 }


// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=

// Interrupt Enable & Disable For Timer 0
void Timer0_Enable_OverFlow_Interrupt(void)
{
	_TIMSK |=Timer0_Interrupt_Enable_Overflow;
}
void Timer0_Disable_OverFlow_Interrupt(void)
{
	_TIMSK &=~Timer0_Interrupt_Enable_Overflow;
}
void Timer0_Enable_Compare_Interrupt(void)
{
	_TIMSK |=Timer0_Interrupt_Enable_Compare;
}
void Timer0_Disable_Compare_Interrupt(void)
{
	_TIMSK &=~Timer0_Interrupt_Enable_Compare;
}
// Interrupt Enable & Disable For Timer 2
void Timer2_Enable_OverFlow_Interrupt(void)
{
	_TIMSK |=Timer2_Interrupt_Enable_Overflow;
}
void Timer2_Disable_OverFlow_Interrupt(void)
{
	_TIMSK &=~Timer2_Interrupt_Enable_Overflow;
}
void Timer2_Enable_Compare_Interrupt(void)
{
	_TIMSK |=Timer2_Interrupt_Enable_Compare;
}
void Timer2_Disable_Compare_Interrupt(void)
{
	_TIMSK &=~Timer2_Interrupt_Enable_Compare;
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// APIS implement
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


/**================================================================
 * @Fn		  - MCAL_Timer8bit_init
 * @brief 	  - initialize the Timer0 
 * @param[in] - Timer0_config_t
 * @retval	  - none
 * Note		  - support Timer 0 and Timer 2 
================================================================**/	
void MCAL_Timer8bit_init(Timer8bit_config_t *Timer8bit_config)
{
	
	uint8_t tempTCCR =0;
	// the mode of the Timer0
	tempTCCR |= Timer8bit_config->Timer8bit_mode;
		
	
	
	// the clock selection
	tempTCCR |=Timer8bit_config->Clock_Select;
	
	
	if(Timer8bit_config->Timer_Number == Timer_Number_ZERO)
	{
		_TCCR0 |=tempTCCR;
		// the OC0 Action
		if(Timer8bit_config->OC_Actio !=OC_disconnected)
		{
			DIO_Pin.DIO_Mood = DIO_Mood_Output;
			DIO_Pin.DIO_PinNumber = DIO_PIN_3;
			MCAL_DIO_init(DIOB,&DIO_Pin);
		}
	}
	else if(Timer8bit_config->Timer_Number == Timer_Number_TWO) 
	{
		_TCCR2 |=tempTCCR;
		if(Timer8bit_config->OC_Actio !=OC_disconnected)
		{
			DIO_Pin.DIO_Mood = DIO_Mood_Output;
			DIO_Pin.DIO_PinNumber = DIO_PIN_7;
			MCAL_DIO_init(DIOD,&DIO_Pin);
		}
	}
	
	if(Timer8bit_config->Timer8bit_mode == Timer8bit_Normal_mode)
	{
		Timer8bit_Mode[Normal_Mode_Index] = *Timer8bit_config;
		MCAL_Timer8bit_Init_Normal_Mode();
	} 
	else if(Timer8bit_config->Timer8bit_mode == Timer8bit_CTC_mode)
	{
		Timer8bit_Mode[CTC_Mode_Index] = *Timer8bit_config;
		MCAL_Timer8bit_Init_CTC_Mode();
	}
		
	else if(Timer8bit_config->Timer8bit_mode == Timer8bit_PWM_mode)
	{
		Timer8bit_Mode[PWM_Mode_Index] = *Timer8bit_config;
		MCAL_Timer8bit_Init_PWM_Mode();
	}
		 
	else if(Timer8bit_config->Timer8bit_mode == Timer8bit_Fast_PWM_mode)
	{
		Timer8bit_Mode[Fast_PWM_Mode_Index] = *Timer8bit_config;
		 MCAL_Timer8bit_Init_Fast_PWM_Mode();
	}	 
}

/**================================================================
 * @Fn		  - MCAL_Timer8bit_Deinit
 * @brief 	  - Stop the Timer0 
 * @param[in] - none
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_Timer8bit_Deinit(uint8_t Timer_Number)
{
	if(Timer_Number == Timer_Number_ZERO)
	{
		_TCCR0 = Clock_Select_No_clock_source;
	}
	else if(Timer_Number == Timer_Number_TWO)
	{
		_TCCR2 = Clock_Select_No_clock_source;
	}
	
}

/**================================================================
 * @Fn		  - MCAL_Timer8bit_UPdate_Counter
 * @brief 	  - Set and update the value of counter register
 * @param[in] - Overflow_value
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_Timer8bit_UPdate_Counter(uint8_t Counter_value)
{
	if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_ZERO)
	{
		_TCNT0 = Counter_value;
	}
	else if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_TWO)
	{
		_TCNT2 = Counter_value;
	}
	
}

/**================================================================
 * @Fn		  - MCAL_Timer8bit_UPdate_Compair
 * @brief 	  - Set and update the value of Compare value 
 * @param[in] - Compair_value
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_Timer8bit_UPdate_Compair(uint8_t Compare_value)
{
	if(Timer8bit_Mode[CTC_Mode_Index].Timer_Number == Timer_Number_ZERO)
	{
		_OCR0 = Compare_value;
	}
	else if(Timer8bit_Mode[CTC_Mode_Index].Timer_Number == Timer_Number_TWO)
	{
		_OCR2 = Compare_value;
	}
}

/**================================================================
 * @Fn		  - MCAL_Timer8bit_GET_Counter_Value
 * @brief 	  - Get the value of Counter Value 
 * @param[in] - none
 * @retval	  - the overflow value
 * Note		  - none
================================================================**/	
uint8_t MCAL_Timer8bit_GET_Counter_Value(void)
{
	uint8_t Value =0;
	if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_ZERO)
	{
		Value = _TCNT0; 
	}
	else if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_TWO)
	{
		Value = _TCNT2; 
	}
	
	return Value ;
}

/**================================================================
 * @Fn		  - MCAL_Timer8bit_GET_Compair_Value
 * @brief 	  - Get the value of Compare
 * @param[in] - none
 * @retval	  - the Compare value
 * Note		  - none
================================================================**/	
uint8_t MCAL_Timer8bit_GET_Compair_Value(void)
{
	uint8_t Value =0;
	if(Timer8bit_Mode[CTC_Mode_Index].Timer_Number == Timer_Number_ZERO)
	{
		Value = _OCR0 ;
	}
	else if(Timer8bit_Mode[CTC_Mode_Index].Timer_Number == Timer_Number_TWO)
	{
		Value = _OCR2;
	}
	return Value;
}

/**================================================================
 * @Fn		  - MCAL_Timer8bit_UPdate_Number_of_overflow
 * @brief 	  - Set and update the number of overflow time
 * @param[in] - the number of overflow time
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_Timer8bit_UPdate_Number_of_overflow(uint32_t Number_Overflow)
{
	if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_ZERO)
	{
		Timer0_Oveflow_Times = Number_Overflow;
	}
	else if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_TWO)
	{
		Timer2_Oveflow_Times = Number_Overflow;
	}
	
}
/**================================================================
 * @Fn		  - MCAL_Timer8bit_GET_Number_of_overflow_Value
 * @brief 	  - Get the number of overflow time
 * @param[in] - none
 * @retval	  - the number of overflow time
 * Note		  - none
================================================================**/	
uint32_t MCAL_Timer8bit_GET_Number_of_overflow_Value(void)
{
	uint32_t value =0;
	if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_ZERO)
	{
		value = Timer0_Oveflow_Times;
	}
	else if(Timer8bit_Mode[Normal_Mode_Index].Timer_Number == Timer_Number_TWO)
	{
		value = Timer2_Oveflow_Times;
	}
	
	return value;
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// ISR
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

 /*Timer 0 compare match interrupt*/
ISR(TIMER0_COMP_vect)
{
	Timer0_IRQ_Compare_value_CallBack();
}

 /*Timer 0 Overflow interrupt*/
ISR(TIMER0_OVF_vect)
{
	Timer0_Oveflow_Times ++;
	Timer0_IRQ_OverFlow_CallBack();
}

/*Timer 2 compare match interrupt*/
ISR(TIMER2_COMP_vect)
{
	Timer2_IRQ_Compare_value_CallBack();
}

/*Timer 2 Overflow interrupt*/
ISR(TIMER2_OVF_vect)
{
	Timer2_Oveflow_Times ++;
	Timer2_IRQ_OverFlow_CallBack();
}