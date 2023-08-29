/*
 * Stepper_Motor.c
 *
 * Created: 28/08/2023 08:04:36 م
 *  Author: GAMA
 */ 

#include "Stepper_Motor.h"

void Stepper_Motor_Init(void)
{
	DIO_PinConfig_t Stepper_Motor;
	Stepper_Motor.DIO_Mood = DIO_Mood_Output;
	Stepper_Motor.DIO_PinNumber = Stepper_Motor_Port;
	MCAL_DIO_init(Stepper_Motor_Port,&Stepper_Motor);
	Stepper_Motor.DIO_PinNumber = Stepper_Motor_Pin_1;
	MCAL_DIO_init(Stepper_Motor_Port,&Stepper_Motor);
	Stepper_Motor.DIO_PinNumber = Stepper_Motor_Pin_2;
	MCAL_DIO_init(Stepper_Motor_Port,&Stepper_Motor);
	Stepper_Motor.DIO_PinNumber = Stepper_Motor_Pin_3;
	MCAL_DIO_init(Stepper_Motor_Port,&Stepper_Motor);
	
}
void Stepper_Motor_Move_CW(uint16_t angle)
{
	#define Stepper_Iteration							(angle/(4*Step_Angle))
	
	for (int i=0;i<Stepper_Iteration;i++)
	{
		// step 1
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_0,DIO_PIN_High);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_1,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_2,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_3,DIO_PIN_Low);
		_delay_ms(50);
		// step 2
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_0,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_1,DIO_PIN_High);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_2,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_3,DIO_PIN_Low);
		_delay_ms(50);
		// step 3
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_0,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_1,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_2,DIO_PIN_High);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_3,DIO_PIN_Low);
		_delay_ms(50);
		// step 4
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_0,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_1,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_2,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_3,DIO_PIN_High);
		_delay_ms(50);	
	}
	
}
void Stepper_Motor_Move_CCW(uint16_t angle)
{
	#define Stepper_Iteration							(angle/(4*Step_Angle))

	for (int i=0;i<Stepper_Iteration;i++)
	{
		// step 1
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_0,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_1,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_2,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_3,DIO_PIN_High);
		_delay_ms(50);
		// step 2
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_0,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_1,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_2,DIO_PIN_High);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_3,DIO_PIN_Low);
		_delay_ms(50);
		// step 3
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_0,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_1,DIO_PIN_High);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_2,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_3,DIO_PIN_Low);
		_delay_ms(50);
		// step 4
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_0,DIO_PIN_High);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_1,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_2,DIO_PIN_Low);
		MCAL_DIO_Write_pin(Stepper_Motor_Port,Stepper_Motor_Pin_3,DIO_PIN_Low);
		_delay_ms(50);
	}
	
	
}