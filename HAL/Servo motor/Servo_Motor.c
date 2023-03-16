/*
 * Servo_Motor.c
 *
 * Created: 16/02/2023 08:04:55 PM
 *  Author: Abdallah Ahmed Mohammed 
 */ 

#include "Includes/Servo_Motor.h"

Timer1_config_t OC1_Pin;
EXTRI_PinConfig_t EXTRI_Pin;
ADC_config_t ADC_Pin;
Servo_Config_t *G_Servo_EXTRI;
void HAL_Servo_Motor_Inint(Servo_Config_t *Servo_Config)
{
	uint32_t Angle_A =(Servo_Config->Degree_OC1A);
	Angle_A *=500;
	Angle_A /=90;
	Angle_A +=999;
	uint32_t Angle_B =(Servo_Config->Degree_OC1B);
	Angle_B *=500;
	Angle_B /=90;
	Angle_B +=999;
	OC1_Pin.Clock_Select = prescaling_8;
	OC1_Pin.ICR1_Value = 19999;
	if (Servo_Config->OC1 == OC1_A)
	{
		OC1_Pin.OCR1A_Value = Angle_A;
		OC1_Pin.Compare_OutputA = Clear_OC1_on_compare_match;
		OC1_Pin.OC1_state = OC1A_ONLY_Connected ;
	}
	else if (Servo_Config->OC1 == OC1_B)
	{
		OC1_Pin.OCR1B_Value = Angle_B;
		OC1_Pin.Compare_OutputB = Clear_OC1_on_compare_match;
		OC1_Pin.OC1_state = OC1B_ONLY_Connected ;
	}
	else if (Servo_Config->OC1 == OC1_A_B)
	{
		OC1_Pin.OCR1A_Value = Angle_A;
		OC1_Pin.OCR1B_Value = Angle_B;
		OC1_Pin.Compare_OutputA = Clear_OC1_on_compare_match;
		OC1_Pin.Compare_OutputB = Clear_OC1_on_compare_match;
		OC1_Pin.OC1_state = OC1A_OC1B_connected ;
	}
	OC1_Pin.Waveform_Generation = Fast_PWM_TOP_ICR1;
	MCAL_Timer1_init(&OC1_Pin);
}
void HAL_Servo_Motor_Deinit()
{
	MCAL_Timer1_GET_OCR1A_Value(0x00);
	MCAL_Timer1_UPdate_OCR1B_Value(0x00);
}


void HAL_Servo_motor_EXTRI_Set(Servo_Config_t *Servo_EXTRI_Config)
{
	G_Servo_EXTRI = Servo_EXTRI_Config;
	EXTRI_Pin.EXTRI_Number = Servo_EXTRI_Config->EXTRI_Number;
	EXTRI_Pin.EXTRI_Case = Servo_EXTRI_Config->EXTRI_Case;
	EXTRI_Pin.P_IRQ_CallBack = EXTRI_Servo_IRQ;
	EXTRI_Pin.IRQ_ENABLE = EXTRI_IRQ_Enable;
	MCAL_EXTRI_GPIO_INIT(&EXTRI_Pin);
	HAL_Servo_Motor_Inint(Servo_EXTRI_Config);
}



// ========================================================

void EXTRI_Servo_IRQ(void)
{
	uint16_t OCRA_value =0;
	uint16_t OCRB_value =0;
	uint32_t A=0;
	uint32_t B=0;
	if (G_Servo_EXTRI->OC1 == OC1_A)
	{
		MCAL_Timer1_GET_OCR1A_Value(&OCRA_value) ;
		A=G_Servo_EXTRI->Counter_A;
		A *=500;
		A /=90;
		OCRA_value = OCRA_value + A; 
		MCAL_Timer1_UPdate_OCR1A_Value(OCRA_value);
	}
	else if (G_Servo_EXTRI->OC1 == OC1_B)
	{
		MCAL_Timer1_GET_OCR1B_Value(&OCRB_value) ;
		B=G_Servo_EXTRI->Counter_B;
		B *=500;
		B /=90;
		OCRB_value = OCRB_value + B;
		MCAL_Timer1_UPdate_OCR1B_Value(OCRB_value);
	}
	else if (G_Servo_EXTRI->OC1 == OC1_A_B)
	{
		MCAL_Timer1_GET_OCR1A_Value(&OCRA_value) ;
		A=G_Servo_EXTRI->Counter_A;
		A *=500;
		A /=90;
		OCRA_value = OCRA_value + A;
		MCAL_Timer1_UPdate_OCR1A_Value(OCRA_value);
		
		
		MCAL_Timer1_GET_OCR1B_Value(&OCRB_value) ;
		B=G_Servo_EXTRI->Counter_B;
		B *=500;
		B /=90;
		OCRB_value = OCRB_value + B;
		MCAL_Timer1_UPdate_OCR1B_Value(OCRB_value);
	}
}