/*
 * ATMEGA_Drivers.c
 *
 * Created: 03/12/2022 12:22:52 م
 * Author : Abdallah Ahmed
 */ 

#include <avr/io.h>
#include "MCAL/Includes/Include_MCAL_files.h"
#include "HAL/Includes/Include_HAL_Files.h"
void IRQ1_callback(void)
{
	MCAL_DIO_Write_Port(DIOA,0xFF);
}

void IRQ2_callback()
{
	MCAL_DIO_Write_Port(DIOA,0x00);
}
int main(void)
{
	DDRA = 0xFF;
// 	LCD_INIT();
// 	Timer1_config_t Timer1;
// 	Timer1.Clock_Select = prescaling_8;
// 	Timer1.Compare_OutputA =Clear_OC1_on_compare_match;
// 	Timer1.Compare_OutputB =Set_OC1_on_compare_match;
// 	Timer1.OC1_state = OC1A_OC1B_connected;
// 	Timer1.OCR1B_Value = 49;
// 	Timer1.OCR1A_Value =49;
// 	Timer1.ICR1_Value = 99;
// //	Timer1.Timer1_Interrupt = Interrupt_Enable_Output_Compare_A_Match;
// 	//Timer1.P_Compare_A_Match_IRQ_Callback = IRQ1_callback;
// //	Timer1.Timer1_Polling = Polling_ON_Output_Compare_A_Match;
// 	Timer1.Waveform_Generation = Fast_PWM_TOP_ICR1;
// 	if(MCAL_Timer1_init(&Timer1) !=FUN_OK)
// 	{
// 		ERROR_HANDELER();
// 	}
// 	Servo_Config_t Servo;
// 	Servo.Degree_OC1A =50;
// 	Servo.Degree_OC1B = 0;
// 	Servo.OC1 = OC1_A;
 	//Servo.EXTRI_Case = EXTRI_Trigger_Rising;
 	//Servo.EXTRI_Number = EXTI_0;
 	//Servo.Counter_A = 20;
 	//Servo.Counter_B = 10;
// 	 Servo.Channel_Number = Inpu_Channel_Single_Ended_ADC0;
// 	HAL_Servo_Motor_Inint(&Servo);
	
	if(MCAL_Timer1_Generate_Frequency_PWM_WITH_Duty(100,10,OC1_A) != FUN_OK)
	{
		ERROR_HANDELER();
	}
	if(MCAL_Timer1_Generate_Frequency_PWM_WITH_Duty(100,40,OC1_B) != FUN_OK)
	{
		ERROR_HANDELER();
	}


	

	
	while(1)
	{

	}
}

