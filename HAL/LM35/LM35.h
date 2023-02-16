/*
 * LM35.h
 *
 * Created: 16/02/2023 11:03:11 ص
 *  Author: Abotaleb
 */ 


#ifndef LM35_H_
#define LM35_H_

#include "Include_HAL_Files.h"

void HAL_LM35_Init(uint8_t Channel_number,uint8_t Voltage_ref);
float HAL_LM35_Get_Vin_Value(void);
float HAL_LM35_Get_Temp_Value(void);
#endif /* LM35_H_ */