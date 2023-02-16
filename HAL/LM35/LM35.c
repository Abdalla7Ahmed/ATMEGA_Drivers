/*
 * LM35.c
 *
 * Created: 16/02/2023 11:02:56 ص
 *  Author: Abotaleb
 */ 
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Includes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "includes/LM35.h"

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Variables
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
DIO_PinConfig_t DIO_Pin;
ADC_config_t ADC_PIN_CONFIG;
uint8_t G_Voltage_ref;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// APIS implement
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void HAL_LM35_Init(uint8_t Channel_number,uint8_t Voltage_ref)
{
	G_Voltage_ref = Voltage_ref;
	ADC_PIN_CONFIG.ADC_Voltage_ref = Voltage_ref;
	ADC_PIN_CONFIG.Inpu_Channel = Channel_number;
	//   =================================================
	ADC_PIN_CONFIG.ADC_Adjust_Result = ADC_Adjust_Result_RIGHT;
	ADC_PIN_CONFIG.ADC_Auto_Trigger = ADC_Auto_Trigger_Enable;
	ADC_PIN_CONFIG.ADC_Auto_Trigger_Source = ADC_Auto_Trigger_Source_Free_Running_mode;
	ADC_PIN_CONFIG.ADC_Interrupt_Enable = ADC_Interrupt_Enable_NONE;
	ADC_PIN_CONFIG.ADC_Prescaler = ADC_Prescaler_128;
	
	MCAL_ADC_init(&ADC_PIN_CONFIG);	
}
float HAL_LM35_Get_Vin_Value(void)
{
	uint16_t Total_Val=0;
	float Vin =0;
	Total_Val = MCAL_GET_ADC_Conversion();
	
	
	if ( (G_Voltage_ref == ADC_Voltage_ref_AVCC_External) ||(G_Voltage_ref == ADC_Voltage_ref_AREF) )
	{
		Vin = (Total_Val * (0.0048828125) );
	}
	else if(G_Voltage_ref == ADC_Voltage_ref_internal_2_56V)
	{
		Vin = (Total_Val * (0.0025) );
	}
	
	 return Vin;
}


float HAL_LM35_Get_Temp_Value(void)
{
	float temp_value =0;
	temp_value = ( (HAL_LM35_Get_Vin_Value()) / (0.01) );
	return temp_value;
}