/*
 * Watchdog.c
 *
 * Created: 08/02/2023 02:33:04 م
 *  Author: Abotaleb
 */ 
#include "Includes/Watchdog.h"


void Watchdog_Enable(uint8_t Tim_out)
{
	switch(Tim_out)
	{
		case  Time_out_2_1_s :
			WDTCR = (1<<WDP0) | (1<<WDP1) |  (1<<WDP2) | (1<<WDE);
			break; 
		case Time_out_1_0_s :
			WDTCR = (1<<WDP1) |  (1<<WDP2) | (1<<WDE);
			break;
		case Time_out_0_52_s :
			WDTCR = (1<<WDP0) |  (1<<WDP2) | (1<<WDE);
			break;
		case Time_out_0_26_s :
			WDTCR = (1<<WDP2) | (1<<WDE);
			break;
		case Time_out_0_13_s :
			WDTCR = (1<<WDP0) | (1<<WDP1) |  (1<<WDE);	
			break;
		case Time_out_65_0_ms :
			WDTCR = (1<<WDP1) | (1<<WDE);
			break;
		case Time_out_32_5_ms :
			WDTCR = (1<<WDP0) | (1<<WDE);
			break;
		case Time_out_16_3_ms :
			WDTCR =(1<<WDE);
			break;

			
	}
	
}
void Watchdog_Disable(void)
{
	WDTCR |=(1<<WDTOE);
	WDTCR |=(1<<WDE);
	WDTCR  = 0;

}

