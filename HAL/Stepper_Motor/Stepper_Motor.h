/*
 * Stepper_Motor.h
 *
 * Created: 28/08/2023 08:04:43 م
 *  Author: GAMA
 */ 


#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ATMEGA32.h"

#define Stepper_Motor_Port							DIOD
#define Stepper_Motor_Pin_0							DIO_PIN_0
#define Stepper_Motor_Pin_1							DIO_PIN_1
#define Stepper_Motor_Pin_2							DIO_PIN_2
#define Stepper_Motor_Pin_3							DIO_PIN_3

#define Step_Angle									2
void Stepper_Motor_Init(void);
void Stepper_Motor_Move_CW(uint16_t angle);
void Stepper_Motor_Move_CCW(uint16_t angle);



#endif /* STEPPER_MOTOR_H_ */