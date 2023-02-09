/*
 * Timer.c
 *
 * Created: 09/02/2023 04:05:54 م
 *  Author: Abotaleb
 */ 

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Includes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "Includes/Timer0.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Macros
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*3


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Variables
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

DIO_PinConfig_t DIO_Pin;

void(* Timer0_IRQ_Compare_value_CallBack)(void);
void(* Timer0_IRQ_OverFlow_CallBack)(void);

uint32_t Number_of_Oveflow =0;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Functions
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
 
 void MCAL_Timer0_Init_Normal_AND_CTC_Mode(Timer0_config_t *Timer0_config)
 {
	 /*
	 COM01	COM00		Description
	 0		0			Normal port operation, OC0 disconnected.
	 0		1			Toggle OC0 on compare match
	 1		0			Clear OC0 on compare match
	 1		1			Set OC0 on compare match
	 */
	 switch(Timer0_config->OCO_Actio)
	 {
		 case OC0_disconnected:
			 _TCCR0 |= OC0_disconnected;
			 break;
		 case Toggle_OC0_on_compare_match:
			 _TCCR0 |= Toggle_OC0_on_compare_match;
			 break;
		 case Clear_OC0_on_compare_match:
			_TCCR0 |= Clear_OC0_on_compare_match;
			 break;
		 case Set_OC0_on_compare_match:
			 _TCCR0 |= Set_OC0_on_compare_match;
			 break;
	 } 
	 
	if(Timer0_config->Interrupt_controle !=Interrupt_Enable_NONE)
	{
		// Enable the interrupt
		_SREG |= (1<<7);
		Timer0_IRQ_Compare_value_CallBack=Timer0_config->P_IRQ_Callback;
		Timer0_IRQ_OverFlow_CallBack=Timer0_config->P_IRQ_Callback;
		_TIMSK |=(Timer0_config->Interrupt_controle == Interrupt_Enable_Compare) ?Interrupt_Enable_Compare:Interrupt_Enable_Overflow;
	}
	else
	{
		if (Timer0_config->Polling_controle == Polling_Enable_Compare)
		{
			while(!(_TIFR & Polling_Enable_Compare));
		}
		else if (Timer0_config->Polling_controle == Polling_Enable_Overflow)
		{
			while(!(_TIFR & Polling_Enable_Overflow));
		}
	}
	
	// the counter value
	MCAL_Timer0_UPdate_Counter(Timer0_config->Timer0_Counter_Register_Value);
	
	// the compare value
	MCAL_Timer0_UPdate_Compare(Timer0_config->Output_Compare_Register_Value);
	 	
 }


 void MCAL_Timer0_Init_PWM_Mode(Timer0_config_t *Timer0_config)
 {
	 /*
	 COM01	COM00		Description
	 0		0			Normal port operation, OC0 disconnected.
	 0		1			Reserved
	 1		0			Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.
	 1		1			Set OC0 on compare match when up-counting. Clear OC0 on comparematch when downcounting.
	 */
	 switch(Timer0_config->OCO_Actio)
	 {
		 case OC0_disconnected:
			_TCCR0 |= OC0_disconnected;
			 break;
		 case Clear_OC0_on_compareUP_set_OCO_at_compareDown:
			 _TCCR0 |= Clear_OC0_on_compareUP_set_OCO_at_compareDown;
			 break;
		 case Set_OC0_on_compareUP_Clear_OCO_at_compareDown:
			 _TCCR0 |= Set_OC0_on_compareUP_Clear_OCO_at_compareDown;
			 break;
	 }
	 
	 // the compare value
	 MCAL_Timer0_UPdate_Compare(Timer0_config->Output_Compare_Register_Value);
	  
 }
 void MCAL_Timer0_Init_Fast_PWM_Mode(Timer0_config_t *Timer0_config)
 {
	 /*
	 COM01	COM00		Description
	 0		0			Normal port operation, OC0 disconnected.
	 0		1			Reserved
	 1		0			Clear OC0 on compare match, set OC0 at BOTTOM, (nin-inverting mode)
	 1		1			Set OC0 on compare match, clear OC0 at BOTTOM, (inverting mode)
	 */
	 switch(Timer0_config->OCO_Actio)
	 {
		 case OC0_disconnected:
			 _TCCR0 |= OC0_disconnected;
			 break;
		case Clear_OC0_on_compare_set_OCO_at_BOTTOM:
			_TCCR0 |= Clear_OC0_on_compare_set_OCO_at_BOTTOM;
			break;
		case Set_OC0_on_compare_Clear_OCO_at_BOTTOM:
			_TCCR0 |= Set_OC0_on_compare_Clear_OCO_at_BOTTOM;
			break;
	 }
	 // the compare value
	 MCAL_Timer0_UPdate_Compare(Timer0_config->Output_Compare_Register_Value);
 }



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// APIS implement
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


/**================================================================
 * @Fn		  - MCAL_Timer0_init
 * @brief 	  - initialize the Timer0 
 * @param[in] - Timer0_config_t
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_Timer0_init(Timer0_config_t *Timer0_config)
{
	
	
	// the mode of the Timer0
	_TCCR0 |= Timer0_config->Timer0_mode;
	
	// the OC0 Action
	if(Timer0_config->OCO_Actio !=OC0_disconnected)
	{
		DIO_Pin.DIO_Mood = DIO_Mood_Output;
		DIO_Pin.DIO_PinNumber = DIO_PIN_3;
		MCAL_DIO_init(DIOB,&DIO_Pin);
	}
	
	// the clock selection
	_TCCR0 |=Timer0_config->Clock_Select;
	
	if((Timer0_config->Timer0_mode == Timer0_Normal_mode) || (Timer0_config->Timer0_mode == Timer0_CTC_mode)) 
		 MCAL_Timer0_Init_Normal_AND_CTC_Mode(Timer0_config);
	else if(Timer0_config->Timer0_mode == Timer0_PWM_mode)
		 MCAL_Timer0_Init_PWM_Mode(Timer0_config);
	else if(Timer0_config->Timer0_mode == Timer0_Fast_PWM_mode)
		 MCAL_Timer0_Init_Fast_PWM_Mode(Timer0_config);
		 
}

/**================================================================
 * @Fn		  - MCAL_Timer0_Deinit
 * @brief 	  - Stop the Timer0 
 * @param[in] - none
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_Timer_Deinit(void)
{
	_TCCR0 = Clock_Select_No_clock_source;
}

/**================================================================
 * @Fn		  - MCAL_Timer0_UPdate_Counter
 * @brief 	  - Set and update the value of counter register
 * @param[in] - Overflow_value
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_Timer0_UPdate_Counter(uint8_t Counter_value)
{
	_TCNT0 = Counter_value;
}

/**================================================================
 * @Fn		  - MCAL_Timer0_UPdate_Compare
 * @brief 	  - Set and update the value of Compare value 
 * @param[in] - Compair_value
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_Timer0_UPdate_Compare(uint8_t Compare_value)
{
	_OCR0 = Compare_value;
}

/**================================================================
 * @Fn		  - MCAL_Timer0_GET_Counter_Value
 * @brief 	  - Get the value of Counter Value 
 * @param[in] - none
 * @retval	  - the overflow value
 * Note		  - none
================================================================**/	
uint8_t MCAL_Timer0_GET_Counter_Value(void)
{
	return _TCNT0;
}

/**================================================================
 * @Fn		  - MCAL_Timer_GET_Compair_Value
 * @brief 	  - Get the value of Compare
 * @param[in] - none
 * @retval	  - the Compare value
 * Note		  - none
================================================================**/	
uint8_t MCAL_Timer0_GET_Compair_Value(void)
{
	return _OCR0;
}

/**================================================================
 * @Fn		  - MCAL_Timer0_UPdate_Number_of_overflow
 * @brief 	  - Set and update the number of overflow time
 * @param[in] - the number of overflow time
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_Timer0_UPdate_Number_of_overflow(uint32_t Number_Overflow)
{
	Number_of_Oveflow = Number_Overflow;
}
/**================================================================
 * @Fn		  - MCAL_Timer0_GET_Number_of_overflow_Value
 * @brief 	  - Get the number of overflow time
 * @param[in] - none
 * @retval	  - the number of overflow time
 * Note		  - none
================================================================**/	
uint32_t MCAL_Timer0_GET_Number_of_overflow_Value(void)
{
	return Number_of_Oveflow;
}



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// ISR
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

ISR(TIMER0_COMP_vect)
{
	Timer0_IRQ_Compare_value_CallBack();
}

ISR(TIMER0_OVF_vect)
{
	Number_of_Oveflow ++;
	Timer0_IRQ_OverFlow_CallBack();
}