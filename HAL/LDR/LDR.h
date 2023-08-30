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
#define LDR_Port									DIOC
#define LDR_Pin										DIO_PIN_0


void HAL_LDR_Init(void);
uint16_t HAL_LDR_Get_Value(void);
 


#endif /* LDR_H_ */