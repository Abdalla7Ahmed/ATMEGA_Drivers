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
	
	Timer8bit_config_t Timer;
	Timer.Timer_Number = Timer_Number_ZERO;
	Timer.Timer8bit_mode = Timer8bit_CTC_mode;
	Timer.Clock_Select = Clock_Select_8_prescaling;
	Timer.Interrupt_controle = Timer0_Interrupt_Enable_Compare;
	Timer.P_Compare_IRQ_Callback= IRQ_callback;
	Timer.OC_Actio=Toggle_OC_on_compare_match;
	Timer.Output_Compare_Register_Value = 0xF5;
	MCAL_Timer8bit_init(&Timer);
	
 	Timer.Timer8bit_mode = Timer8bit_CTC_mode;
 	Timer.Timer_Number = Timer_Number_TWO;
 	Timer.Clock_Select = Clock_Select_8_prescaling;
 	//Timer.Interrupt_controle = TimerInterrupt_Enable_Compare;
 	Timer.P_Compare_IRQ_Callback= IRQ_callback;
 	Timer.OC_Actio=Toggle_OC_on_compare_match;
 	Timer.Output_Compare_Register_Value = 0x5;
 	MCAL_Timer8bit_init(&Timer);
	while(1)
	{

	}
}

