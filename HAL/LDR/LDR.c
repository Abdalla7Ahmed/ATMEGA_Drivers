/*
 * LDR.c
 *
 * Created: 30/08/2023 03:31:23 م
 *  Author: GAMA
 */ 
#include "includes/LDR.h"

void HAL_LDR_Init(void)
{

	
	ADC_config_t ADC_PIN_CONFIG;
	
	ADC_PIN_CONFIG.ADC_Adjust_Result = ADC_Adjust_Result_RIGHT;
	ADC_PIN_CONFIG.ADC_Auto_Trigger = ADC_Auto_Trigger_Enable;
	ADC_PIN_CONFIG.ADC_Auto_Trigger_Source = ADC_Auto_Trigger_Source_Free_Running_mode;
	ADC_PIN_CONFIG.ADC_Interrupt_Enable = ADC_Interrupt_Enable_CC;
	ADC_PIN_CONFIG.ADC_Prescaler = ADC_Prescaler_128;
	ADC_PIN_CONFIG.ADC_Voltage_ref = ADC_Voltage_ref_internal_2_56V;
	ADC_PIN_CONFIG.Inpu_Channel = LDR_Pin;
	ADC_PIN_CONFIG.P_IRQ_Callback = HAL_LDR_Get_Value;
	MCAL_ADC_init(&ADC_PIN_CONFIG);
	
		
}
uint16_t HAL_LDR_Get_Value(void)
{
	return MCAL_GET_ADC_Conversion();
}