/*
 * ADC.h
 *
 * Created: 10/02/2023 03:56:15 م
 *  Author: Abotaleb
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "ATMEGA32.h"
#include "Include_MCAL_files.h"

typedef struct  
{
	uint8_t ADC_Voltage_ref;			// must be set @ref ADC_Voltage_ref_define
	uint8_t ADC_Adjust_Result;			// must be set @ref ADC_Adjust_Result_define
	uint8_t Inpu_Channel;				// must be set @ref Inpu_Channel_define
	uint8_t ADC_Auto_Trigger;			// must be set @ref ADC_Auto_Trigger_define
	uint8_t ADC_Interrupt_Enable;		// must be set @ref ADC_Interrupt_Enable_define
	uint8_t ADC_Prescaler ;				// must be set @ref ADC_Prescaler_define
	uint8_t ADC_Auto_Trigger_Source;	// must be set @ref ADC_Auto_Trigger_Source_define
	uint8_t ADC_Auto_Trigger_Compare_Value;
	void (*P_IRQ_Callback)(void);
}ADC_config_t;







//@ref ADC_Voltage_ref_define
#define ADC_Voltage_ref_AREF								(uint8_t)(0x0)   //AREF, Internal Vref turned off	
#define ADC_Voltage_ref_AVCC_External						(uint8_t)(1<<6)	 //AVCC with external capacitor at AREF pin
#define ADC_Voltage_ref_internal_2_56V						(uint8_t)((1<<6) | (1<<7)) //Internal 2.56V Voltage Reference with external capacitor at AREF pin


//ADC_Adjust_Result_define
#define ADC_Adjust_Result_RIGHT								(uint8_t)(0x0)   //Write zero to ADLAR to right adjust the result.
#define ADC_Adjust_Result_LEFT								(uint8_t)(1<<5)	 //Write one to ADLAR to left adjust the result.



//@ref Inpu_Channel_define
// single ended
#define Inpu_Channel_Single_Ended_ADC0						(uint8_t)(0x0) 
#define Inpu_Channel_Single_Ended_ADC1						(uint8_t)(0x1) 
#define Inpu_Channel_Single_Ended_ADC2						(uint8_t)(0x2) 
#define Inpu_Channel_Single_Ended_ADC3						(uint8_t)(0x3) 
#define Inpu_Channel_Single_Ended_ADC4						(uint8_t)(0x4) 
#define Inpu_Channel_Single_Ended_ADC5						(uint8_t)(0x5) 
#define Inpu_Channel_Single_Ended_ADC6						(uint8_t)(0x6) 
#define Inpu_Channel_Single_Ended_ADC7						(uint8_t)(0x7) 

#define Inpu_Channel_Single_Ended_1_22Vbg					(uint8_t)(0x1E)
#define Inpu_Channel_Single_Ended_0_GND						(uint8_t)(0x1F)

// Differential
#define Inpu_Channel_Differential_PADC0_NADC0_G10			(uint8_t)(0x8 ) //positive = ADC0 , Negative = ADC0, Gain = 10x
#define Inpu_Channel_Differential_PADC1_NADC0_G10			(uint8_t)(0x9 ) //positive = ADC1 , Negative = ADC0, Gain = 10x
#define Inpu_Channel_Differential_PADC0_NADC0_G200			(uint8_t)(0xA ) //positive = ADC0 , Negative = ADC0, Gain = 200x
#define Inpu_Channel_Differential_PADC1_NADC0_G200			(uint8_t)(0xB ) //positive = ADC1 , Negative = ADC0, Gain = 200x
#define Inpu_Channel_Differential_PADC2_NADC2_G10			(uint8_t)(0xC ) //positive = ADC2 , Negative = ADC2, Gain = 10x
#define Inpu_Channel_Differential_PADC3_NADC2_G10			(uint8_t)(0xD ) //positive = ADC3 , Negative = ADC2, Gain = 10x
#define Inpu_Channel_Differential_PADC2_NADC2_G200			(uint8_t)(0xE ) //positive = ADC2 , Negative = ADC2, Gain = 200x
#define Inpu_Channel_Differential_PADC3_NADC2_G200			(uint8_t)(0xF ) //positive = ADC3 , Negative = ADC2, Gain = 200x
#define Inpu_Channel_Differential_PADC0_NADC1_G1			(uint8_t)(0x10) //positive = ADC0 , Negative = ADC1, Gain = 1x
#define Inpu_Channel_Differential_PADC1_NADC1_G1			(uint8_t)(0x11) //positive = ADC1 , Negative = ADC1, Gain = 1x
#define Inpu_Channel_Differential_PADC2_NADC1_G1			(uint8_t)(0x12) //positive = ADC2 , Negative = ADC1, Gain = 1x
#define Inpu_Channel_Differential_PADC3_NADC1_G1			(uint8_t)(0x13) //positive = ADC3 , Negative = ADC1, Gain = 1x
#define Inpu_Channel_Differential_PADC4_NADC1_G1			(uint8_t)(0x14) //positive = ADC4 , Negative = ADC1, Gain = 1x
#define Inpu_Channel_Differential_PADC5_NADC1_G1			(uint8_t)(0x15) //positive = ADC5 , Negative = ADC1, Gain = 1x
#define Inpu_Channel_Differential_PADC6_NADC1_G1			(uint8_t)(0x16) //positive = ADC6 , Negative = ADC1, Gain = 1x
#define Inpu_Channel_Differential_PADC7_NADC1_G1			(uint8_t)(0x17) //positive = ADC7 , Negative = ADC1, Gain = 1x
#define Inpu_Channel_Differential_PADC0_NADC2_G1			(uint8_t)(0x18) //positive = ADC0 , Negative = ADC2, Gain = 1x
#define Inpu_Channel_Differential_PADC1_NADC2_G1			(uint8_t)(0x19) //positive = ADC1 , Negative = ADC2, Gain = 1x
#define Inpu_Channel_Differential_PADC2_NADC2_G1			(uint8_t)(0x1A) //positive = ADC2 , Negative = ADC2, Gain = 1x
#define Inpu_Channel_Differential_PADC3_NADC2_G1			(uint8_t)(0x1B) //positive = ADC3 , Negative = ADC2, Gain = 1x
#define Inpu_Channel_Differential_PADC4_NADC2_G1			(uint8_t)(0x1C) //positive = ADC4 , Negative = ADC2, Gain = 1x
#define Inpu_Channel_Differential_PADC5_NADC2_G1			(uint8_t)(0x1D) //positive = ADC5 , Negative = ADC2, Gain = 1x


//@ref ADC_Auto_Trigger_define
#define ADC_Auto_Trigger_Disable							(uint8_t)(0x0)
#define ADC_Auto_Trigger_Enable								(uint8_t)(1<<5)


//@ref ADC_Interrupt_Enable_define
#define ADC_Interrupt_Enable_NONE							(uint8_t)(0x0)
#define ADC_Interrupt_Enable_CC								(uint8_t)(1<<3) // conversion completes interrupt

//@ref ADC_Prescaler_define
#define ADC_Prescaler_0										(uint8_t)(0x0)
#define ADC_Prescaler_2										(uint8_t)(0x1)
#define ADC_Prescaler_4										(uint8_t)(0x2)
#define ADC_Prescaler_8										(uint8_t)(0x3)
#define ADC_Prescaler_16									(uint8_t)(0x4)
#define ADC_Prescaler_32									(uint8_t)(0x5)
#define ADC_Prescaler_64									(uint8_t)(0x6)
#define ADC_Prescaler_128									(uint8_t)(0x7)


//@ref ADC_Auto_Trigger_Source_define
#define ADC_Auto_Trigger_Source_Free_Running_mode			(uint8_t)(0x0)
#define ADC_Auto_Trigger_Source_Analog_Comparator			(uint8_t)(0x1)
#define ADC_Auto_Trigger_Source_EXI0						(uint8_t)(0x2)
#define ADC_Auto_Trigger_Source_Timerr0_Compare_Match		(uint8_t)(0x3)
#define ADC_Auto_Trigger_Source_Timerr0_Overflow			(uint8_t)(0x4)
#define ADC_Auto_Trigger_Source_Timerr1_Compare_Match		(uint8_t)(0x5)
#define ADC_Auto_Trigger_Source_Timerr1_Overflow			(uint8_t)(0x6)
#define ADC_Auto_Trigger_Source_Timerr1_Capture_Event		(uint8_t)(0x7)




//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// APIS 
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void MCAL_ADC_init(ADC_config_t *ADC_PinConfig);
void MCAL_ADC_DEinit(void);

uint16_t MCAL_GET_ADC_Conversion(void);



#endif /* ADC_H_ */