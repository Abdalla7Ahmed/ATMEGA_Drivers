/*
 * LDR.h
 *
 * Created: 30/08/2023 03:31:31 م
 *  Author: GAMA
 */ 


#ifndef LDR_H_
#define LDR_H_
#include "../../MCAL/Includes/DIO.h"
#include "../../MCAL/Includes/ADC.h"
#define LDR_Port									DIOA
#define LDR_Pin										Inpu_Channel_Single_Ended_ADC0


void HAL_LDR_Init(void);
uint16_t HAL_LDR_Get_Value(void);
 


#endif /* LDR_H_ */