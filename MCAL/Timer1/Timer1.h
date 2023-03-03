/*
 * Timer16bit.h
 *
 * Created: 23/02/2023 10:33:12 ص
 *  Author: Abotaleb
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include "Include_MCAL_files.h"

/*OC1A and OC1B Mode*/
typedef enum
{
	/*
	============= NORMAL AND CTCMODE =============
	COM1A1/COM1B1		COM1A0/COM1B0	 Description
	0					0				Normal port operation, OC1A/OC1Bdisconnected.
	0					1				Toggle OC1A/OC1B on compare match
	1					0				Clear OC1A/OC1B on compare match (Set output to low level)
	1					1				Set OC1A/OC1B on compare match (Set output to high level)
	*/
	OC1_disconnected  = 0,
	Toggle_OC1_on_compare_match,
	Clear_OC1_on_compare_match,
	Set_OC1_on_compare_match,
	/*
	 ============= FAST PWM MODE =============
	COM1A1/COM1B1		COM1A0/COM1B0	Description
	0					0				Normal port operation, OC1A/OC1Bdisconnected.
	0					1				WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).For all other WGM13:0 settings, normal port operation, OC1A/OC1B disconnected.
	1					0				Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM,(non-inverting mode)
	1					1				Set OC1A/OC1B on compare match, clear OC1A/OC1B at BOTTOM,(inverting mode)
	*/
	Reserved1 =0,
	Toggle_OC1A_Compare_OC1B_disconnected_FAST_PWM,
	Clear_OC1_compare_set_OC1_BOTTOM,
	Set_OC1_compare_Clear_OC1_BOTTOM,
	
	/*
	============= Phase Correct and Phase and Frequency Correct PWM =============
	
	COM1A1/COM1B1		COM1A0/COM1B0	Description
	0					0				Normal port operation, OC1A/OC1B disconnected.
	0					1				WGM13:0 = 9 or 14: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).For all other WGM13:0 settings, normal port operation, OC1A/OC1B disconnected.
	1					0				Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare match when down-counting.
	1					1				Set OC1A/OC1B on compare match when up-counting. Clear OC1A/OC1B on compare match when down-counting.
	*/
	Reserved2 =0,
	Toggle_OC1A_Compare_OC1B_disconnected_PWM,
	Clear_OC1_Up_Set_OC1_down,
	Set_OC1_Up_Set_Clear_down
}Compare_Output_Mode;

typedef enum 
{
	OC1A_OC1B_Disconnected=0,
	OC1A_ONLY_Connected,
	OC1B_ONLY_Connected,
	OC1A_OC1B_connected,
}OC1_Action;
/*Waveform Generation Mode*/
typedef enum
{					
											  // TOP	 ||   Update of OCR1x  ||   TOV1 Flag Set on
	Normal_TOP_0xFFFF,						  // 0xFFFF		  Immediate				MAX
	PWM_Phase_Correct_8_bit_TOP_0x00FF,		  // 0x00FF		  TOP					BOTTOM
	PWM_Phase_Correct_9_bit_TOP_0x01FF,		  // 0x01FF		  TOP					BOTTOM
	PWM_Phase_Correct_10_bit_TOP_0x03FF,	  // 0x03FF		  TOP					BOTTOM
	CTC_TOP_OCR1A,							  // OCR1A		  Immediate				MAX
	Fast_PWM_8_bit_TOP_0x00FF,				  // 0x00FF		  BOTTOM				TOP
	Fast_PWM_9_bit_TOP_0x01FF,				  // 0x01FF		  BOTTOM				TOP
	Fast_PWM_10_bit_TOP_0x03FF,				  // 0x03FF		  BOTTOM				TOP
	PWM_Phase_and_Frequency_Correct_TOP_ICR1, // ICR1		  BOTTOM				BOTTOM
	PWM_Phase_and_Frequency_Correct_TOP_OCR1A,// OCR1A		  BOTTOM			    BOTTOM
	PWM_Phase_Correct_TOP_ICR1,				  // ICR1		  TOP				    BOTTOM
	PWM_Phase_Correct_TOP_OCR1A,			  // OCR1A		  TOP				    BOTTOM
	CTC_TOP_ICR1,							  // ICR1		  Immediate			    MAX
	Reserved,								  // Reserved 
	Fast_PWM_TOP_ICR1,						  // ICR1		  BOTTOM				TOP
	Fast_PWM_TOP_OCR1A						  // OCR1A        BOTTOM				TOP

}Waveform_Generation_Mode;

/* Input Capture */
typedef struct
{
	uint8_t Input_Capture_Noise_Canceler;		// must set according to @ref Input_Capture_Noise_Canceler_define
	uint8_t Input_Capture_Edge_Select;			// must set according to @ref Input_Capture_Edge_Select_define
}Input_Capture_Mode;



/* Clock Select */
typedef enum
{
	No_clock_source,
	NO_prescaling,
	prescaling_8,
	prescaling_64,
	prescaling_256,
	prescaling_1024,
	External_Failing,
	External_Rising
}Clock_Select_Mode;



typedef struct
{
	Compare_Output_Mode	Compare_OutputA	;
	Compare_Output_Mode	Compare_OutputB	;	
	OC1_Action OC1_state;
	Waveform_Generation_Mode Waveform_Generation;
	Input_Capture_Mode Input_Capture;
	Clock_Select_Mode Clock_Select;
	uint8_t Timer1_Interrupt ;			// must set according to @ref Interrupt_define
	uint8_t Timer1_Polling ;			// must set according to @ref Polling_define   in case using interrupt , polling doesn't mean anything 
	uint16_t TCNT1_Value;
	uint16_t OCR1A_Value;
	uint16_t OCR1B_Value;
	uint16_t ICR1_Value;
	void(* P_Input_Capture_IRQ_Callback  )(void);
	void(* P_Compare_A_Match_IRQ_Callback)(void);
	void(* P_Compare_B_Match_IRQ_Callback)(void);
	void(* P_Overflow_IRQ_Callback       )(void);
}Timer1_config_t;


//@ref Input_Capture_Noise_Canceler_define
#define Input_Capture_Noise_Canceler_Disable					(uint8_t)(0x0)
#define Input_Capture_Noise_Canceler_Enable						(uint8_t)(1<<7)


//@ref Input_Capture_Edge_Select_define
#define Input_Capture_Edge_Select_Failing						(uint8_t)(0x0)
#define Input_Capture_Edge_Select_Rising						(uint8_t)(1<<6)


//@ref Interrupt_define
#define Interrupt_Disable										(uint8_t)(0x0)
#define Interrupt_Input_Capture									(uint8_t)(1<<5)
#define Interrupt_Enable_Output_Compare_A_Match					(uint8_t)(1<<4)
#define Interrupt_Enable_Output_Compare_B_Match					(uint8_t)(1<<3)
#define Interrupt_Enable_Overflow								(uint8_t)(1<<2)


//@ref Polling_define
#define Polling_ON_Input_Capture								(uint8_t)(1<<5)
#define Polling_ON_Output_Compare_A_Match						(uint8_t)(1<<4)
#define Polling_ON_Output_Compare_B_Match						(uint8_t)(1<<3)
#define Polling_ON_Overflow										(uint8_t)(1<<2)

typedef enum 
{
	FUN_NOK,
	FUN_OK
}Func_State;

// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// *==================== APIS ==========================*
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
Func_State MCAL_Timer1_init(Timer1_config_t *Timer1_config);
Func_State MCAL_Timer1_Deinit(void);

Func_State MCAL_Timer1_UPdate_TCNT1_Value(uint16_t TCNT1_Value);
Func_State MCAL_Timer1_GET_TCNT1_Value(uint16_t *TCNT1_Value);

Func_State MCAL_Timer1_UPdate_Number_of_overflow(uint32_t Number_Overflow);
Func_State MCAL_Timer1_GET_Number_of_overflow_Value(uint32_t *Number_Overflow);

Func_State MCAL_Timer1_UPdate_OCR1A_Value(uint16_t OCR1A_Value);
Func_State MCAL_Timer1_GET_OCR1A_Value(uint16_t *OCR1A_Value);


Func_State MCAL_Timer1_UPdate_OCR1B_Value(uint16_t OCR1B_Value);
Func_State MCAL_Timer1_GET_OCR1B_Value(uint16_t *OCR1B_Value);

Func_State MCAL_Timer1_UPdate_ICR1_Value(uint16_t ICR1_Value);
Func_State MCAL_Timer1_GET_ICR1_Value(uint16_t *ICR1_Value);

Func_State MCAL_Timer1_UPdate_OCR1A_immediate(void);
Func_State MCAL_Timer1_UPdate_OCR1B_immediate(void);

Func_State MCAL_Timer1_Get_Frequencry_PWM(uint32_t *Frequency);
Func_State MCAL_Timer1_Get_Duty_Cycle_PWM(uint8_t *Duty_percent, uint8_t OC1_NO);

Func_State MCAL_Timer1_Generate_Frequency_PWM_WITH_Duty(uint32_t Frequency_KHZ,uint8_t Duty_Cycle_PR,uint8_t OC1_NO);
Func_State MCAL_Timer1_Generate_Duty_Cycle(uint8_t Duty_percent);

void ERROR_HANDELER(void);


#endif /* TIMER1_H_ */