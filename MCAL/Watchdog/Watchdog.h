/*
 * Watchdog.h
 *
 * Created: 08/02/2023 02:33:15 م
 *  Author: Abotaleb
 */ 


#ifndef WATCHDOG_H_
#define WATCHDOG_H_



#include "ATMEGA32.h"

void Watchdog_Enable(uint8_t Tim_out);
void Watchdog_Disable(void);


#define Time_out_16_3_ms								(uint8_t)(0x0)
#define Time_out_32_5_ms								(uint8_t)(0x1)
#define Time_out_65_0_ms								(uint8_t)(0x2)
#define Time_out_0_13_s									(uint8_t)(0x3)
#define Time_out_0_26_s									(uint8_t)(0x4)
#define Time_out_0_52_s									(uint8_t)(0x5)
#define Time_out_1_0_s									(uint8_t)(0x6)
#define Time_out_2_1_s									(uint8_t)(0x7)


#endif /* WATCHDOG_H_ */