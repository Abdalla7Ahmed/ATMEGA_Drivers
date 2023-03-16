/*
 * Ultrasonic_Sensor.h
 *
 * Created: 16/02/2023 05:35:25 م
 *  Author: Abotaleb
 */ 


#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include "Include_HAL_Files.h"

#define Ultasonic_PORT				DIOC


void HAL_Ultrasonic_Init(); 
void HAL_Ultrasonic_Start(uint8_t DIO_Number);
uint8_t HAL_Ultrasonic_Get_Distansc(uint8_t *Distance);


#endif /* ULTRASONIC_SENSOR_H_ */