/*
 * ADC.c
 *
 * Created: 10/02/2023 03:56:06 م
 *  Author: Abotaleb
 */ 

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Includes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "Includes/ADC.h"

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Macros
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*3

#define ADC_Disable()								(_ADCSRA &=~(1<<7))
#define ADC_Enable()								(_ADCSRA |= (1<<7))
#define ADC_Start_Conversion()						(_ADCSRA |= (1<<6)) // this bit clear after conversion

#define NULL										(void*)(0)

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Variables
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void(* ADC_IRQ_Conversion_Complete_CallBack)(void);
ADC_config_t *GADC_config = NULL;
DIO_PinConfig_t DIO_Pin;
EXTRI_PinConfig_t EXTRI_Pin;
Timer0_config_t Timer0_Pin;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Functions
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void SET_DIO_Channel(uint8_t Channel)
{
	switch(Channel)
	{
		case Inpu_Channel_Single_Ended_ADC0:
		case Inpu_Channel_Differential_PADC0_NADC0_G10:
		case Inpu_Channel_Differential_PADC0_NADC0_G200:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_0;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Single_Ended_ADC1:
		case Inpu_Channel_Differential_PADC1_NADC1_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_1;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Single_Ended_ADC2:
		case Inpu_Channel_Differential_PADC2_NADC2_G10:
		case Inpu_Channel_Differential_PADC2_NADC2_G200:
		case Inpu_Channel_Differential_PADC2_NADC2_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_2;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Single_Ended_ADC3:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_3;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Single_Ended_ADC4:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_4;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Single_Ended_ADC5:
			DIO_Pin.DIO_PinNumber = DIO_PIN_5;
			MCAL_DIO_init(DIOA,&DIO_Pin);
		break;
		case Inpu_Channel_Single_Ended_ADC6:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_6;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Single_Ended_ADC7:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_7;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC1_NADC0_G200:
		case Inpu_Channel_Differential_PADC0_NADC1_G1:
		case Inpu_Channel_Differential_PADC1_NADC0_G10: 
			DIO_Pin.DIO_PinNumber = DIO_PIN_1;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_PinNumber = DIO_PIN_0;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC3_NADC2_G10:
		case Inpu_Channel_Differential_PADC3_NADC2_G200:
		case Inpu_Channel_Differential_PADC3_NADC2_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_3;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_2;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC2_NADC1_G1:
		case Inpu_Channel_Differential_PADC1_NADC2_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_2;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_1;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC3_NADC1_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_3;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_1;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC4_NADC1_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_4;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_1;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC5_NADC1_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_5;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_1;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC6_NADC1_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_6;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_1;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC7_NADC1_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_7;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_1;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC0_NADC2_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_0;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_2;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC4_NADC2_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_4;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_2;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
		case Inpu_Channel_Differential_PADC5_NADC2_G1:
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_5;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			DIO_Pin.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_Pin.DIO_PinNumber = DIO_PIN_2;
			MCAL_DIO_init(DIOA,&DIO_Pin);
			break;
	}
}


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// APIS implement
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


/**================================================================
 * @Fn		  - MCAL_ADC_init
 * @brief 	  - initialize the ADC 
 * @param[in] - ADC_config_t
 * @retval	  - none
 * Note		  - none
================================================================**/	

void MCAL_ADC_init(ADC_config_t *ADC_PinConfig)
{
	
	GADC_config = ADC_PinConfig;


	// Select the Voltage Reference 
	_ADMUX |= ADC_PinConfig->ADC_Voltage_ref;
	
	// ADC Adjust Result 
	_ADMUX |= ADC_PinConfig->ADC_Adjust_Result;
	
	// the input channel
	_ADMUX |= ADC_PinConfig->Inpu_Channel;

	SET_DIO_Channel(ADC_PinConfig->Inpu_Channel);
	
	// Auto trigger case 
	_ADCSRA |= ADC_PinConfig->ADC_Auto_Trigger;
	
	// the Prescaler
	_ADCSRA |= ADC_PinConfig->ADC_Prescaler;
	
	if(ADC_PinConfig->ADC_Auto_Trigger)
	{
		_SFIOR |=ADC_PinConfig->ADC_Auto_Trigger_Source;
		
		switch(ADC_PinConfig->ADC_Auto_Trigger_Source)
		{
			case ADC_Auto_Trigger_Source_EXI0:
				EXTRI_Pin.EXTRI_Number = EXTI_0;
				EXTRI_Pin.EXTRI_Case = EXTRI_Trigger_Rising;
				EXTRI_Pin.IRQ_ENABLE = EXTRI_IRQ_Enable;
				MCAL_EXTRI_GPIO_INIT(&EXTRI_Pin);
				break;
			case ADC_Auto_Trigger_Source_Timerr0_Compare_Match:
				Timer0_Pin.Timer0_mode = Timer0_CTC_mode;
				Timer0_Pin.Clock_Select = Clock_Select_8_prescaling;
				Timer0_Pin.Interrupt_controle = Interrupt_Enable_Compare;
				Timer0_Pin.OCO_Actio=OC0_disconnected;
				Timer0_Pin.Output_Compare_Register_Value = ADC_PinConfig->ADC_Auto_Trigger_Compare_Value;
				MCAL_Timer0_init(&Timer0_Pin);
				break;
			case ADC_Auto_Trigger_Source_Timerr0_Overflow:
				Timer0_Pin.Timer0_mode = Timer0_Normal_mode;
				Timer0_Pin.Clock_Select = Clock_Select_8_prescaling;
				Timer0_Pin.Interrupt_controle = Interrupt_Enable_Overflow;
				Timer0_Pin.OCO_Actio=OC0_disconnected;
				MCAL_Timer0_init(&Timer0_Pin);
				break;
			case ADC_Auto_Trigger_Source_Timerr1_Compare_Match:
			case ADC_Auto_Trigger_Source_Timerr1_Overflow:
			case ADC_Auto_Trigger_Source_Timerr1_Capture_Event:
				// not supported yet
				break;	
		}
	}
	
	
	// Enable the ADC module
	ADC_Enable();
	// Start Conversion
	ADC_Start_Conversion();
	
	
	if(ADC_PinConfig->ADC_Interrupt_Enable == ADC_Interrupt_Enable_CC)
	{
		// Enable the interrupt
		_SREG |= (1<<7);
		
		_ADCSRA |=ADC_Interrupt_Enable_CC;
		ADC_IRQ_Conversion_Complete_CallBack = ADC_PinConfig->P_IRQ_Callback;
	}
	else 
	{
		 // polling mechanism
		while(!(_ADCSRA &(1<<4)));          
	}
}
/**================================================================
 * @Fn		  - MCAL_ADC_DEinit
 * @brief 	  - Deinit the ADC Module  
 * @param[in] - none
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_ADC_DEinit(void)
{
	_ADMUX = 0x00;
	_ADCSRA = 0x00;
	_SFIOR = 0x00;
	
}
/**================================================================
 * @Fn		  - MCAL_GET_ADC_Conversion
 * @brief 	  - Get the value of ADC conversion 
 * @param[in] - none
 * @retval	  - the value
 * Note		  - none
================================================================**/	
uint16_t MCAL_GET_ADC_Conversion(void)
{
	uint8_t Low_Value = 0;
	uint8_t High_Value = 0;
	uint16_t Total_Value=0;
	
	if(GADC_config->ADC_Adjust_Result == ADC_Adjust_Result_LEFT)
	{
		Low_Value = _ADCL;
		High_Value = _ADCH;
		Low_Value = Low_Value >> 6;
		Total_Value = ( (Low_Value) | (High_Value <<2));
		
	} 
	else if(GADC_config->ADC_Adjust_Result == ADC_Adjust_Result_RIGHT)
	{
		Low_Value = _ADCL;
		High_Value = _ADCH;
		Total_Value = ( (Low_Value) | (High_Value <<8) );
	}
	return Total_Value;
}



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// ISR
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

ISR(ADC_vect)
{
	ADC_IRQ_Conversion_Complete_CallBack();
	
	// start conversion 
	ADC_Start_Conversion();
}