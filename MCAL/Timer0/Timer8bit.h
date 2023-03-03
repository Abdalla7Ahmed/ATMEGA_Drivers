/*
 * Timer.h
 *
 * Created: 09/02/2023 04:05:39 م
 *  Author: Abotaleb
 */ 


#ifndef TIMER8BIT_H_
#define TIMER8BIT_H_

#include "Include_MCAL_files.h"

typedef struct  
{	
	uint8_t Timer_Number ;						// must set according to @ref Timer_Number_define
	uint8_t Timer8bit_mode ;					// must set according to @ref Timer8bit_defien_mode
	uint8_t OC_Actio;							// must set according to @ref OC_Actio_define
	uint8_t Clock_Select;						// must set according to @ref Clock_Select_define
	uint8_t Timer8bit_Counter_Register_Value;
	uint8_t Output_Compare_Register_Value;
	uint8_t Interrupt_controle;					// must set according to @ref Interrupt_Enable_define
	uint8_t Polling_controle;					// must set according to @ref Polling_Enable_define
	
	void(* P_Compare_IRQ_Callback)(void);
	void(* P_OverFlow_IRQ_Callback)(void); 
}Timer8bit_config_t;

//@ref Timer_Number_mode
#define Timer_Number_ZERO											(uint8_t)(0x0)
#define Timer_Number_TWO											(uint8_t)(0x1)


//@ref Timer8bit_defien_mode																								
#define Timer8bit_Normal_mode										(uint8_t)(0x0)		
#define Timer8bit_PWM_mode											(uint8_t)(1<<6)		
#define Timer8bit_CTC_mode											(uint8_t)(1<<3)
#define Timer8bit_Fast_PWM_mode										(uint8_t)( (1<<6) | (1<<3)) 

//@ref OC_Actio_define
// at normal mode and compare mode 
#define OC_disconnected											(uint8_t)(0x0)
#define Toggle_OC_on_compare_match								(uint8_t)(1<<4)
#define Clear_OC_on_compare_match								(uint8_t)(1<<5)
#define Set_OC_on_compare_match									(uint8_t)( (1<<4) | (1<<5)) 
// at Fast PWM mode
#define Clear_OC_on_compare_set_OC_at_BOTTOM					(uint8_t)(1<<5) //Clear OC0 on compare match, set OC0 at BOTTOM,(nin-inverting mode)
#define Set_OC_on_compare_Clear_OC_at_BOTTOM					(uint8_t)( (1<<4) | (1<<5)) //Set OC0 on compare match, clear OC0 at BOTTOM,(inverting mode)
// at Phase Correct PWM Mode 
#define Clear_OC_on_compareUP_set_OC_at_compareDown				(uint8_t)(1<<5) //Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.
#define Set_OC_on_compareUP_Clear_OC_at_compareDown				(uint8_t)( (1<<4) | (1<<5)) //Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting.

//@ref Clock_Select_define
#define Clock_Select_No_clock_source							(uint8_t)(0x0)
#define Clock_Select_NO_prescaling								(uint8_t)(0x1)
#define Clock_Select_8_prescaling								(uint8_t)(0x2)
#define Clock_Select_64_prescaling								(uint8_t)(0x3)
#define Clock_Select_256_prescaling								(uint8_t)(0x4)
#define Clock_Select_1024_prescaling							(uint8_t)(0x5)
#define Clock_Select_External_Failing							(uint8_t)(0x6)  //External clock source on T0 pin. Clock on falling edge.			
#define Clock_Select_External_Rising							(uint8_t)(0x7)	// External clock source on T0 pin. Clock on rising edge.									

//@ref Interrupt_define
#define Interrupt_Enable_NONE									(uint8_t)(0x0) // Disable the interrupt
#define Timer0_Interrupt_Enable_Compare							(uint8_t)(1<<1) // Output Compare Match Interrupt Enable 
#define Timer0_Interrupt_Enable_Overflow						(uint8_t)(1<<0) // Overflow Interrupt Enable
#define Timer2_Interrupt_Enable_Compare							(uint8_t)(1<<7) // Output Compare Match Interrupt Enable
#define Timer2_Interrupt_Enable_Overflow						(uint8_t)(1<<6) // Overflow Interrupt Enable

// @ref Polling_Enable_define
#define Polling_Enable_NONE										(uint8_t)(0x0)	// Disable the Polling
#define Timer0_Polling_Enable_Compare							(uint8_t)(1<<1) // Output Compare Match Polling
#define Timer0_Polling_Enable_Overflow							(uint8_t)(1<<0) // Overflow Polling
#define Timer2_Polling_Enable_Compare							(uint8_t)(1<<7) // Output Compare Match Polling
#define Timer2_Polling_Enable_Overflow							(uint8_t)(1<<6) // Overflow Polling

// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// *==================== APIS ==========================*
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
void MCAL_Timer8bit_init(Timer8bit_config_t *Timer8bit_config);
void MCAL_Timer8bit_Deinit(uint8_t Timer_Number);

void MCAL_Timer8bit_UPdate_Counter(uint8_t Counter_value);
uint8_t MCAL_Timer8bit_GET_Counter_Value(void);

void MCAL_Timer8bit_UPdate_Number_of_overflow(uint32_t Number_Overflow);
uint32_t MCAL_Timer8bit_GET_Number_of_overflow_Value(void);

void MCAL_Timer8bit_UPdate_Compair(uint8_t Compare_value);
uint8_t MCAL_Timer8bit_GET_Compair_Value(void);




#endif /* TIMER8BIT_H_ */