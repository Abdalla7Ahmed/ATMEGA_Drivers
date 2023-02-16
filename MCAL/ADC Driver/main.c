/*
 * ATMEGA_Drivers.c
 *
 * Created: 03/12/2022 12:22:52 م
 * Author : Abdallah Ahmed
 */ 

#include <avr/io.h>
#include "MCAL/Includes/Include_MCAL_files.h"



void IRQ_callback(void)
{
	MCAL_DIO_Write_Port(DIOD,(uint8_t)MCAL_GET_ADC_Conversion());
	MCAL_DIO_Write_Port(DIOC,(uint8_t)(MCAL_GET_ADC_Conversion() >>8));
}


int main(void)
{
	DIO_PinConfig_t DIO_PORT;
	DIO_PORT.DIO_Mood = DIO_Mood_Output;
	MCAL_DIO_init_PORT(DIOD,&DIO_PORT);
	DIO_PORT.DIO_Mood = DIO_Mood_Output;
	MCAL_DIO_init_PORT(DIOC,&DIO_PORT);

	ADC_config_t ADC_PIN_CONFIG;
	ADC_PIN_CONFIG.ADC_Adjust_Result = ADC_Adjust_Result_RIGHT;
	ADC_PIN_CONFIG.ADC_Auto_Trigger = ADC_Auto_Trigger_Enable;
	ADC_PIN_CONFIG.ADC_Auto_Trigger_Source = ADC_Auto_Trigger_Source_Free_Running_mode;
	ADC_PIN_CONFIG.ADC_Interrupt_Enable = ADC_Interrupt_Enable_CC;
	ADC_PIN_CONFIG.ADC_Prescaler = ADC_Prescaler_128;
	ADC_PIN_CONFIG.ADC_Voltage_ref = ADC_Voltage_ref_AREF;
	ADC_PIN_CONFIG.Inpu_Channel = Inpu_Channel_Single_Ended_ADC0;
	ADC_PIN_CONFIG.P_IRQ_Callback = IRQ_callback;
	MCAL_ADC_init(&ADC_PIN_CONFIG);
	
	while(1)
	{
	}
}

