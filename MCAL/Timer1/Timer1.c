/*
 * Timer16bit.c
 *
 * Created: 23/02/2023 10:32:40 ص
 *  Author: Abotaleb
 */ 
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Includes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "Includes/Timer1.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Macros
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define No_Clock_Sourc										(uint8_t)(0x0)
#define NULL												(void *)(0)
#define OC1A												0
#define OC1B												1	
#define OC1_A_B												2

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Variables
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Timer1_config_t *G_Timer1_config = NULL;
DIO_PinConfig_t DIO_Pin;
static void(* Timer1_IRQ_Input_Capture_CallBack  )(void) = NULL;
static void(* Timer1_IRQ_Compare_A_Match_CallBack)(void) = NULL;
static void(* Timer1_IRQ_Compare_B_Match_CallBack)(void) = NULL;
static void(* Timer1_IRQ_OverFlow_CallBack       )(void) = NULL;
static uint32_t Timer1_Oveflow_Times =0;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Functions
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void MCAL_Get_Top_Value(uint16_t *TOP_Value)
{
	uint16_t Value =0;
	switch (G_Timer1_config->Waveform_Generation)
	{
		case Normal_TOP_0xFFFF :
			Value = (0xFFFF -1);
			break ;
		case PWM_Phase_Correct_8_bit_TOP_0x00FF :
			Value = (0xFFFF -1);
			break ;
		case PWM_Phase_Correct_9_bit_TOP_0x01FF :
			Value = (0x01FF -1);
			break ;
		case PWM_Phase_Correct_10_bit_TOP_0x03FF :
			Value = (0x03FF -1);
			break ;
		case CTC_TOP_OCR1A :
			MCAL_Timer1_GET_OCR1A_Value(&Value);
			break ;
		case Fast_PWM_8_bit_TOP_0x00FF :
			Value = (0x00FF -1);
			break ;
		case Fast_PWM_9_bit_TOP_0x01FF :
			Value = (0x01FF -1);
			break ;
		case Fast_PWM_10_bit_TOP_0x03FF :
			Value = (0x03FF -1);
			break ;
		case PWM_Phase_and_Frequency_Correct_TOP_ICR1 :
			MCAL_Timer1_GET_ICR1_Value(&Value);
			break ;
		case PWM_Phase_and_Frequency_Correct_TOP_OCR1A :
			MCAL_Timer1_GET_OCR1A_Value(&Value);
			break ;
		case PWM_Phase_Correct_TOP_ICR1 :
			MCAL_Timer1_GET_ICR1_Value(&Value);
			break ;
		case PWM_Phase_Correct_TOP_OCR1A :
			MCAL_Timer1_GET_OCR1A_Value(&Value);
			break ;
		case CTC_TOP_ICR1 :
			MCAL_Timer1_GET_ICR1_Value(&Value);
			break ;
		case Fast_PWM_TOP_ICR1 :
			MCAL_Timer1_GET_ICR1_Value(&Value);
			break ;
		case Fast_PWM_TOP_OCR1A :
			MCAL_Timer1_GET_OCR1A_Value(&Value);
			break ;
	}
	*((uint16_t*)TOP_Value) =(uint16_t)(Value);
}


void ERROR_HANDELER(void)
{
	while(1);
}

/* ========= General Interrupt ========= */
void General_Interrupt_Enable(void)
{
	_SREG |= (1<<7);
}
void General_Interrupt_Disable(void)
{
	_SREG &= ~(1<<7);
}

/* ========= OverFlow Interrupt ========= */
void Timer1_Enable_OverFlow_Interrupt(void)
{
	General_Interrupt_Enable();
	_TIMSK |=Interrupt_Enable_Overflow;
}
void Timer1_Disable_OverFlow_Interrupt(void)
{
	General_Interrupt_Disable();
	_TIMSK &=~Interrupt_Enable_Overflow;
}

/* ========= Compare_A Interrupt ========= */
void Timer1_Enable_Compare_A_Interrupt(void)
{
	General_Interrupt_Enable();		
	_TIMSK |=Interrupt_Enable_Output_Compare_A_Match;
}
void Timer1_Disable_Compare_A_Interrupt(void)
{
	General_Interrupt_Disable();
	_TIMSK &=~Interrupt_Enable_Output_Compare_A_Match;
}

/* ========= Compare_B Interrupt ========= */
void Timer1_Enable_Compare_B_Interrupt(void)
{
	General_Interrupt_Disable();
	_TIMSK |=Interrupt_Enable_Output_Compare_B_Match;
}
void Timer1_Disable_Compare_B_Interrupt(void)
{
	_TIMSK &=~Interrupt_Enable_Output_Compare_B_Match;
}

/* ========= Input Capture Interrupt ========= */
void Timer1_Enable_Input_Capture_Interrupt(void)
{
	General_Interrupt_Enable();
	_TIMSK |=Interrupt_Input_Capture;
}
void Timer1_Disable_Input_Capture_Interrupt(void)
{
	General_Interrupt_Disable();
	_TIMSK &=~Interrupt_Input_Capture;
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// APIS implement
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


/**================================================================
 * @Fn		  - MCAL_Timer1_init
 * @brief 	  - initialize the Timer1 
 * @param[in] - Timer1_config_t
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_init(Timer1_config_t *Timer1_config)
{
	Func_State State = FUN_NOK; 
	
	G_Timer1_config = Timer1_config;
	// set the mode of wave generation 
	switch (Timer1_config->Waveform_Generation)
	{
		case Normal_TOP_0xFFFF :
			_TCCR1A |=Normal_TOP_0xFFFF;
			break ;
		case PWM_Phase_Correct_8_bit_TOP_0x00FF :
			_TCCR1A |=PWM_Phase_Correct_8_bit_TOP_0x00FF;
			break ;
		case PWM_Phase_Correct_9_bit_TOP_0x01FF :
			_TCCR1A |=PWM_Phase_Correct_9_bit_TOP_0x01FF;
			break ;
		case PWM_Phase_Correct_10_bit_TOP_0x03FF :
			_TCCR1A |=PWM_Phase_Correct_10_bit_TOP_0x03FF;
			break ;
		case CTC_TOP_OCR1A :
			_TCCR1A |=CTC_TOP_OCR1A;
			SETBIT(_TCCR1B,3); // WGM12
			break ;
		case Fast_PWM_8_bit_TOP_0x00FF :
			_TCCR1A |=Fast_PWM_8_bit_TOP_0x00FF;
			SETBIT(_TCCR1B,3);// WGM12
			break ;
		case Fast_PWM_9_bit_TOP_0x01FF :
			_TCCR1A |=Fast_PWM_9_bit_TOP_0x01FF;
			SETBIT(_TCCR1B,3);// WGM12
			break ;
		case Fast_PWM_10_bit_TOP_0x03FF :
			_TCCR1A |=Fast_PWM_10_bit_TOP_0x03FF;
			SETBIT(_TCCR1B,3);// WGM12
			break ;
		case PWM_Phase_and_Frequency_Correct_TOP_ICR1 :
			_TCCR1A |=PWM_Phase_and_Frequency_Correct_TOP_ICR1;
			SETBIT(_TCCR1B,4); // WGM13
			break ;
		case PWM_Phase_and_Frequency_Correct_TOP_OCR1A :
			_TCCR1A |=PWM_Phase_and_Frequency_Correct_TOP_OCR1A;
			SETBIT(_TCCR1B,4); // WGM13
			break ;
		case PWM_Phase_Correct_TOP_ICR1 :
			_TCCR1A |=PWM_Phase_Correct_TOP_ICR1;
			SETBIT(_TCCR1B,4); // WGM13
			break ;
		case PWM_Phase_Correct_TOP_OCR1A :
			_TCCR1A |=PWM_Phase_Correct_TOP_OCR1A;
			SETBIT(_TCCR1B,4); // WGM13
			break ;
		case CTC_TOP_ICR1 :
			_TCCR1A |=CTC_TOP_ICR1;
			SETBIT(_TCCR1B,4); // WGM13
			SETBIT(_TCCR1B,3);// WGM12
			break ;
		case Fast_PWM_TOP_ICR1 :
			_TCCR1A |=Fast_PWM_TOP_ICR1;
			SETBIT(_TCCR1B,4); // WGM13
			SETBIT(_TCCR1B,3);// WGM12
			break ;
		case Fast_PWM_TOP_OCR1A :
			_TCCR1A |=Fast_PWM_TOP_OCR1A;
			SETBIT(_TCCR1B,4); // WGM13
			SETBIT(_TCCR1B,3);// WGM12
			break ;	
	}
	
	
	// OC1 Action
	if(Timer1_config->OC1_state !=OC1A_OC1B_Disconnected)
	{
		if(Timer1_config->OC1_state)
		{
			if(Timer1_config->OC1_state == OC1A_ONLY_Connected)
			{
				// Set the OC1A Action
				_TCCR1A |=( (Timer1_config->Compare_OutputA)<<6);
				// Init OC1A as an output
				DIO_Pin.DIO_Mood = DIO_Mood_Output ; 
				DIO_Pin.DIO_PinNumber = DIO_PIN_5;
				MCAL_DIO_init(DIOD,&DIO_Pin);
				
			}
			else if(Timer1_config->OC1_state == OC1B_ONLY_Connected)
			{
				// Set the OC1B Action
				_TCCR1A |=( (Timer1_config->Compare_OutputB)<<4);
				// Init OC1B as an output
				DIO_Pin.DIO_Mood = DIO_Mood_Output ;
				DIO_Pin.DIO_PinNumber = DIO_PIN_4;
				MCAL_DIO_init(DIOD,&DIO_Pin);
			}	
			else if(Timer1_config->OC1_state == OC1A_OC1B_connected)
			{
				// set the OC1A Action
				_TCCR1A |=( (Timer1_config->Compare_OutputA)<<6); 
				// set the OC1B Action 
				_TCCR1A |=( (Timer1_config->Compare_OutputB)<<4);
				// Init OC1A as an output
				DIO_Pin.DIO_Mood = DIO_Mood_Output ;
				DIO_Pin.DIO_PinNumber = DIO_PIN_5;
				MCAL_DIO_init(DIOD,&DIO_Pin);
				// Init OC1B as an output
				DIO_Pin.DIO_Mood = DIO_Mood_Output ;
				DIO_Pin.DIO_PinNumber = DIO_PIN_4;
				MCAL_DIO_init(DIOD,&DIO_Pin);
				
			}
		}
	}
	
	// clock select 
	_TCCR1B |=Timer1_config->Clock_Select;
	
	// the input capture 
	_TCCR1B |=Timer1_config->Input_Capture_Noise_Canceler;
	_TCCR1B |=Timer1_config->Input_Capture_Edge_Select;
	
	// the interrupt control
	if(Timer1_config->Timer1_Interrupt !=Interrupt_Disable)
	{
		General_Interrupt_Enable ();
		_TIMSK |= Timer1_config->Timer1_Interrupt;
		Timer1_IRQ_Input_Capture_CallBack = Timer1_config->P_Input_Capture_IRQ_Callback;
		Timer1_IRQ_OverFlow_CallBack = Timer1_config->P_Overflow_IRQ_Callback;
		Timer1_IRQ_Compare_A_Match_CallBack = Timer1_config->P_Compare_A_Match_IRQ_Callback;
		Timer1_IRQ_Compare_B_Match_CallBack = Timer1_config->P_Compare_B_Match_IRQ_Callback;
	}
	else
	{
		if(Timer1_config->Timer1_Polling == Polling_ON_Input_Capture)
		{
			while (! (_TIFR & (Polling_ON_Input_Capture)));
		}
		if(Timer1_config->Timer1_Polling ==Polling_ON_Output_Compare_A_Match )
		{
			while (! (_TIFR & (Polling_ON_Output_Compare_A_Match)));
		}
		if(Timer1_config->Timer1_Polling ==Polling_ON_Output_Compare_B_Match )
		{
			while (! (_TIFR & (Polling_ON_Output_Compare_B_Match)));
		}
		if(Timer1_config->Timer1_Polling ==Polling_ON_Overflow )
		{
			while (! (_TIFR & (Polling_ON_Overflow)));
		}
	}

	/* ============ Set TCNT1 Value ============*/
	MCAL_Timer1_UPdate_TCNT1_Value(Timer1_config->TCNT1_Value);
	/* ============ Set OCR1A Value ============*/
	MCAL_Timer1_UPdate_OCR1A_Value(Timer1_config->OCR1A_Value);
	/* ============ Set OCR1B Value ============*/
	MCAL_Timer1_UPdate_OCR1B_Value(Timer1_config->OCR1B_Value);
	/* ============ Set ICR1 Value ============*/
	MCAL_Timer1_UPdate_ICR1_Value(Timer1_config->ICR1_Value);
	
	State = FUN_OK;
	
	return State;
}

/**================================================================
 * @Fn		  - MCAL_Timer1_Deinit
 * @brief 	  - De initialize the Timer1 
 * @param[in] - none
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_Deinit(void)
{
	Func_State State = FUN_NOK;
	
	_TCCR1B = No_Clock_Sourc;
	
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_UPdate_TCNT1_Value
 * @brief 	  - UPdate TCNT1 Value
 * @param[in] - the TCNT1 value
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	

Func_State MCAL_Timer1_UPdate_TCNT1_Value(uint16_t TCNT1_Value)
{
	Func_State State = FUN_NOK;
	_TCNT1H = (uint8_t)(TCNT1_Value>>8);
	_TCNT1L = (uint8_t)TCNT1_Value;
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_GET_TCNT1_Value
 * @brief 	  - Get TCNT1 Value
 * @param[in] - the pointer to TCNT1 value
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_GET_TCNT1_Value(uint16_t *TCNT1_Value)
{
	Func_State State = FUN_NOK;
	*((uint16_t*)TCNT1_Value) =(uint16_t)( _TCNT1L | (_TCNT1H <<8) );
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_UPdate_Number_of_overflow
 * @brief 	  - UPdate Number of overflow Value
 * @param[in] - the Number of overflow
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_UPdate_Number_of_overflow(uint32_t Number_Overflow)
{
	Func_State State = FUN_NOK;
	Timer1_Oveflow_Times =Number_Overflow;
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_GET_Number_of_overflow_Value
 * @brief 	  - Get Number of overflow Value
 * @param[in] - the pointer to overflow value
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_GET_Number_of_overflow_Value(uint32_t *Number_Overflow)
{
	Func_State State = FUN_NOK;
	*((uint32_t*)Number_Overflow) =(uint32_t)(Timer1_Oveflow_Times);
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_UPdate_OCR1A_Value
 * @brief 	  - UPdate OCR1A Value
 * @param[in] - the OCR1A value
 * @retval	  - state of the function  NOK , OK
 * Note		  - in case of using OCR1A as TOP of wave generation , OCR1A is Disconnected 
				and the wave generation will be in OCR1B
================================================================**/	
Func_State MCAL_Timer1_UPdate_OCR1A_Value(uint16_t OCR1A_Value)
{
	Func_State State = FUN_NOK;
	_OCR1AH = (uint8_t)(OCR1A_Value>>8);
	_OCR1AL = (uint8_t)OCR1A_Value;
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_GET_OCR1A_Value
 * @brief 	  - Get OCR1A Value
 * @param[in] - the pointer to overflow value
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_GET_OCR1A_Value(uint16_t *OCR1A_Value)
{
	Func_State State = FUN_NOK;
	*((uint16_t*)OCR1A_Value) =(uint16_t)( _OCR1AL | (_OCR1AH <<8) );
	State = FUN_OK;
	return State;
}

/**================================================================
 * @Fn		  - MCAL_Timer1_UPdate_OCR1B_Value
 * @brief 	  - UPdate OCR1B Value
 * @param[in] - the OCR1B value
 * @retval	  - state of the function  NOK , OK
 * Note		  - in case of using OCR1B as TOP of wave generation , OCR1B is Disconnected
				and the wave generation will be in OCR1A
================================================================**/	
Func_State MCAL_Timer1_UPdate_OCR1B_Value(uint16_t OCR1B_Value)
{
	Func_State State = FUN_NOK;
	_OCR1BH = (uint8_t)(OCR1B_Value>>8);
	_OCR1BL = (uint8_t)OCR1B_Value;
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_GET_OCR1B_Value
 * @brief 	  - Get OCR1B Value
 * @param[in] - the pointer to OCR1B value
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_GET_OCR1B_Value(uint16_t *OCR1B_Value)
{
	Func_State State = FUN_NOK;
	*((uint16_t*)OCR1B_Value) =(uint16_t)( _OCR1BL | (_OCR1BH <<8) );
	return FUN_OK;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_UPdate_ICR1_Value
 * @brief 	  - UPdate ICR1 Value
 * @param[in] - the ICR1 value
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_UPdate_ICR1_Value(uint16_t ICR1_Value)
{
	Func_State State = FUN_NOK;
	_ICR1H = (uint8_t)(ICR1_Value>>8);
	_ICR1L = (uint8_t)ICR1_Value;
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_GET_ICR1_Value
 * @brief 	  - Get ICR1 Value
 * @param[in] - the pointer to ICR1 value
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_GET_ICR1_Value(uint16_t *ICR1_Value)
{
	Func_State State = FUN_NOK;
	//uint8_t ICR1L_Value =0;
	//uint8_t ICR1H_Value =0;
	
	*((uint16_t*)ICR1_Value) =(uint16_t)( _ICR1L | (_ICR1H <<8) );
	State = FUN_OK;
	return State;
}


/**================================================================
 * @Fn		  - MCAL_Timer1_UPdate_OCR1A_immediate
 * @brief 	  - Update OCR1A Value immediate
 * @param[in] - none
 * @retval	  - state of the function  NOK , OK
 * Note		  - active when the WGM13:0 bits specifies a non-PWM mode 
				When writing a logical one to the FOC1A/FOC1B bit,
			    an immediate compare match is forced on the Waveform Generation unit.
================================================================**/	
Func_State MCAL_Timer1_UPdate_OCR1A_immediate(void)
{
	Func_State State = FUN_NOK;
	_TCCR1A |= 1<<3;
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_UPdate_OCR1B_immediate
 * @brief 	  - Update OCR1B Value immediate
 * @param[in] - none
 * @retval	  - state of the function  NOK , OK
 * Note		  - active when the WGM13:0 bits specifies a non-PWM mode 
				When writing a logical one to the FOC1A/FOC1B bit,
			    an immediate compare match is forced on the Waveform Generation unit.
================================================================**/	
Func_State MCAL_Timer1_UPdate_OCR1B_immediate(void)
{
	Func_State State = FUN_NOK;
	_TCCR1A |= 1<<2;
	State = FUN_OK;
	return State;
}

/**================================================================
 * @Fn		  - MCAL_Timer1_Get_Frequencry_PWM
 * @brief 	  - Get the frequency of PWM 
 * @param[in] - Pointer to the Frequency value
 * @retval	  - state of the function  NOK , OK
 * Note		  - none
================================================================**/	
Func_State MCAL_Timer1_Get_Frequencry_PWM(uint32_t *Frequency)
{
	Func_State State = FUN_NOK;
	uint32_t Timer_Freq =0;
	uint32_t PWM_freq = 0;
	uint16_t TOP_Value=0;
	uint16_t prescaling_Value =0;
	
	switch(G_Timer1_config->Clock_Select)
	{
		case NO_prescaling:
			prescaling_Value =1;
			break;
		case prescaling_8:
			prescaling_Value =8;
			break;
		case prescaling_64:
			prescaling_Value =64;
			break;
		case prescaling_256:
			prescaling_Value =256;
			break;
		case prescaling_1024:
			prescaling_Value =1024;
			break;
		
	}
	Timer_Freq = ( (uint32_t)F_CPU / prescaling_Value);
	MCAL_Get_Top_Value(&TOP_Value);
	
	PWM_freq = (Timer_Freq / (TOP_Value+1));
	*((uint32_t*)Frequency) =(uint32_t)(PWM_freq);
	
	State = FUN_OK;
	return State;
}

/**================================================================
 * @Fn		  - MCAL_Timer1_Get_Duty_Cycle_PWM
 * @brief 	  - Get the Duty Cycle of the wave generation 
 * @param[in] - Pointer to the Duty cycle percent
 * @param[in] - OC1_NO can be OC1A or OC1B
 * @retval	  - state of the function  NOK , OK
 * Note		  - the value of Duty cycle will be in percent
================================================================**/	
Func_State MCAL_Timer1_Get_Duty_Cycle_PWM(uint8_t *Duty_percent , uint8_t OC1_NO)
{
	Func_State State = FUN_NOK;

	uint16_t TOP_Value=0;
	uint16_t OCR1_Vale =0;
	uint8_t Duty_Cycle= 0;

	if(OC1_NO == OC1A)
	{
		MCAL_Timer1_GET_OCR1A_Value(&OCR1_Vale);
	}
	else if(OC1_NO == OC1B)
	{
		MCAL_Timer1_GET_OCR1B_Value(&OCR1_Vale);
	}
	


	MCAL_Get_Top_Value(&TOP_Value);

	
	Duty_Cycle = ( (OCR1_Vale+1) *100) /(TOP_Value+1);
	
	
	*((uint8_t*)Duty_percent) =(uint8_t)(Duty_Cycle);
	
	State = FUN_OK;
	return State;
}
/**================================================================
 * @Fn		  - MCAL_Timer1_Generate_Frequencry_PWM
 * @brief 	  - Set the PWM frequency in unit KHZ 
 * @param[in] - the Frequency
 * @param[in] - the Duty Cycle
 * @param[in] - OC1_NO can be OC1A or OC1B
 * @retval	  - state of the function  NOK , OK
 * Note		  - if the both OCRA and OCRB will generate PWM they will operate only in
 * 				one frequency and one or two diffrent duty cycle according to the OCR1A 
 * 				and OCR1B Values  
================================================================**/	
Func_State MCAL_Timer1_Generate_Frequency_PWM_WITH_Duty(uint32_t Frequency_KHZ,uint8_t Duty_Cycle_PR,uint8_t OC1_NO)
{
	Func_State State = FUN_NOK;
	Timer1_config_t PWM_F;
	uint16_t ICR_Temp =0;
	uint16_t OCR_Temp =0;
	
	uint8_t flag = 0;

	PWM_F.Clock_Select = NO_prescaling;
	if(Frequency_KHZ > 0 && Frequency_KHZ < 8000)
	{
		ICR_Temp = (uint32_t)F_CPU / (Frequency_KHZ * 1000);
		flag ++ ;
	}
	if(Duty_Cycle_PR >0 && Duty_Cycle_PR <100 )
	{
		OCR_Temp = ( (ICR_Temp *Duty_Cycle_PR ) / 100);
		flag ++;
	}
	
	switch(OC1_NO)
	{
		case OC1A:
			PWM_F.OCR1A_Value =OCR_Temp ;
			PWM_F.Compare_OutputA = Clear_OC1_on_compare_match;
			PWM_F.OC1_state = OC1A_ONLY_Connected;
			break;
		case OC1B :
			PWM_F.OCR1B_Value = OCR_Temp;
			PWM_F.Compare_OutputB = Clear_OC1_on_compare_match;
			PWM_F.OC1_state = OC1B_ONLY_Connected;
			break;
	}
	PWM_F.Waveform_Generation = Fast_PWM_TOP_ICR1;
	PWM_F.ICR1_Value = ICR_Temp;
	
	if(MCAL_Timer1_init(&PWM_F) && (flag == 2) )
	{
		State = FUN_OK;
		flag = 0;
	}
	
	return State;
}


// ISR
ISR(TIMER1_CAPT_vect)
{
	if(Timer1_IRQ_Input_Capture_CallBack != NULL)
	{
		Timer1_IRQ_Input_Capture_CallBack();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(Timer1_IRQ_Compare_A_Match_CallBack != NULL)
	{
		Timer1_IRQ_Compare_A_Match_CallBack();
	}
	
}
ISR(TIMER1_COMPB_vect)
{
	if(Timer1_IRQ_Compare_B_Match_CallBack != NULL)
	{
		Timer1_IRQ_Compare_B_Match_CallBack();
	}
}
ISR(TIMER1_OVF_vect)
{
	if(Timer1_IRQ_OverFlow_CallBack != NULL)
	{
		Timer1_Oveflow_Times++;
		Timer1_IRQ_OverFlow_CallBack();
	}
}