/*
 * ATMEGA_Drivers.c
 *
 * Created: 03/12/2022 12:22:52 م
 * Author : Abdallah Ahmed
 */ 

#include "MCAL/Includes/Include_MCAL_files.h"
#include "HAL/Includes/Include_HAL_Files.h"


void IRQ_callback(void)
{
	MCAL_DIO_Write_Port(DIOD,(uint8_t)MCAL_GET_ADC_Conversion());
	MCAL_DIO_Write_Port(DIOC,(uint8_t)(MCAL_GET_ADC_Conversion() >>8));
}


int main(void)
{
	
	LCD_INIT();
	
	
	HAL_LM35_Init(Inpu_Channel_Single_Ended_ADC1,ADC_Voltage_ref_AVCC_External);
	LCD_WRITE_STRING("Temp--> ");
	LCD_GOTO_XY(1,1);
	LCD_WRITE_STRING("Vin--> ");
	while(1)
	{
		LCD_GOTO_XY(0,8);
		LCD_display_real_number(HAL_LM35_Get_Temp_Value());
		_ADCSRA |= (1<<6);
		LCD_GOTO_XY(1,8);
		LCD_display_real_number(HAL_LM35_Get_Vin_Value());

	}
}

