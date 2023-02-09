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
	MCAL_DIO_Toggle_Port(DIOA);
}


int main(void)
{
	DDRA = 0xFF;
	
	Timer0_config_t Timer0;
	Timer0.Timer0_mode = Timer0_Fast_PWM_mode;
	Timer0.Clock_Select = Clock_Select_8_prescaling;
	//Timer0.Interrupt_controle = Interrupt_Enable_Compare;
	Timer0.P_IRQ_Callback = IRQ_callback;
	Timer0.OCO_Actio=Clear_OC0_on_compare_set_OCO_at_BOTTOM;
	Timer0.Output_Compare_Register_Value = 0xF0;
	MCAL_Timer0_init(&Timer0);
	
	while(1)
	{

	}
}

