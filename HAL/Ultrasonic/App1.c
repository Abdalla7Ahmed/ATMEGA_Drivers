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
	PORTA = 0x1;
}

void IRQ2_callback()
{
	PORTA = 0x0;
}
int main(void)
{
	//DDRA = 0xFF;
	//DDRB = 0xFF;
	LCD_INIT();
// 	Timer1_config_t Timer1;
// 	Timer1.Clock_Select = prescaling_8;
// 	Timer1.Compare_OutputA = Toggle_OC1_on_compare_match;
// 	Timer1.Compare_OutputB = Toggle_OC1_on_compare_match;
// 	Timer1.OC1_state = OC1A_OC1B_connected;
//  	Timer1.OCR1B_Value = 50000;
//  	Timer1.OCR1A_Value =20;
//  	//Timer1.ICR1_Value = 50000;
// 	Timer1.Timer1_Interrupt = Interrupt_Enable_Output_Compare_A_Match | Interrupt_Enable_Output_Compare_B_Match  ;
// 	Timer1.P_Compare_A_Match_IRQ_Callback = IRQ1_callback;
// 	Timer1.P_Compare_B_Match_IRQ_Callback = IRQ2_callback;
// 	//Timer1.Timer1_Polling = Polling_ON_Output_Compare_A_Match;
// 	Timer1.Waveform_Generation  = Normal_TOP_0xFFFF;
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
	
	//MCAL_Timer1_Generate_Frequency_PWM_WITH_Duty(100,10,OC1_A) ;

//	MCAL_Timer1_Generate_Frequency_PWM_WITH_Duty(100,40,OC1_B) ;
	Ultrasonic_Init();
	
	uint8_t d;
	while(1)
	{
		HAL_Ultrasonic_Start(DIO_PIN_0);
		if(HAL_Ultrasonic_Get_Distansc(&d))
		{
			LCD_GOTO_XY(0,0);
			LCD_display_number(d);
		}

		HAL_Ultrasonic_Start(DIO_PIN_1);
		if(HAL_Ultrasonic_Get_Distansc(&d))
		{
			LCD_GOTO_XY(0,7);
			LCD_display_number(d);

		}
		
		HAL_Ultrasonic_Start(DIO_PIN_2);
		if(HAL_Ultrasonic_Get_Distansc(&d))
		{
			LCD_GOTO_XY(1,0);
			LCD_display_number(d);
		}
		
		HAL_Ultrasonic_Start(DIO_PIN_3);
		if(HAL_Ultrasonic_Get_Distansc(&d))
		{
			LCD_GOTO_XY(1,7);
			LCD_display_number(d);
		}
	}
}

