/*
 * Servo_Motor.h
 *
 * Created: 16/02/2023 08:05:05 م
 *  Author: Abotaleb
 */ 


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_


#include "Include_HAL_Files.h"





typedef struct
{
	uint8_t Degree_OC1A;
	uint8_t Degree_OC1B;	
	uint8_t OC1;					// must set according to @ref OC1_define 
	
	uint8_t Channel_Number;			// this option only work if you choose Mode_Unconstant_Degree_FROM_ADC
	uint8_t EXTRI_Number;			// this option only work if you choose Mode_Unconstant_Degree_FROM_EXTEI
	uint8_t EXTRI_Case;				// this option only work if you choose Mode_Unconstant_Degree_FROM_EXTEI
	uint8_t Counter_A;				// this option only work if you choose Mode_Unconstant_Degree_FROM_EXTEI
	uint8_t Counter_B;				// this option only work if you choose Mode_Unconstant_Degree_FROM_EXTEI
									// the increment of degree every one EXTRI
	void(*P_IRQ_Callback)(void);
}Servo_Config_t;



//@ref OC1_define 
#define OC1_A												0
#define OC1_B												1
#define OC1_A_B												2


void HAL_Servo_Motor_Inint(Servo_Config_t *Servo_Config);
void HAL_Servo_Motor_Deinit();
void HAL_Servo_Motor_ADC_Set(Servo_Config_t *Servo_ADC_Config);
void HAL_Servo_motor_EXTRI_Set(Servo_Config_t *Servo_EXTRI_Config);

void EXTRI_Servo_IRQ(void);


#endif /* SERVO_MOTOR_H_ */