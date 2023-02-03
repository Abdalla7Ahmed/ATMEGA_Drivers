/*
 * Interrupt.h
 *
 * Created: 17/12/2022 07:03:33 م
 *  Author: Abotaleb
 */ 


#ifndef EXTRI_H_
#define EXTRI_H_

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Includes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include <avr/interrupt.h>
#include "Include_MCAL_files.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// User type definitions
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	// determine the interrupt number 
	// this parameter is set by @ref EXTI_define 
	uint8_t EXTRI_Number           ; 
	// determine the interrupt case
	// this parameter is set by @ref EXTRI_Trigger_define
	uint8_t EXTRI_Case			   ;
	// Enable or Disable the external interrupt .
	// the parameters can be set based on @ref EXTRI_IRQ_define.
	uint8_t IRQ_ENABLE			   ;
	// pointer to function that hold ISR of the interrupt
	void (*P_IRQ_CallBack)(void)   ;
	
}EXTRI_PinConfig_t;



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Macros configuration references
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//@ref EXTI_define
#define EXTI_0						0
#define EXTI_1						1
#define EXTI_2						2

//@ref EXTRI_Trigger_define
#define EXTRI_Trigger_Lowlevel                0x00U     // 0b0000 0000
#define EXTRI_Trigger_RisingANDFailing        0x01U		// 0b0000 0001
#define EXTRI_Trigger_Failing                 0x02U		// 0b0000 0010
#define EXTRI_Trigger_Rising                  0x03U		// 0b0000 0011

// @ref EXTRI_IRQ_define.
#define EXTRI_IRQ_Disable                     0
#define EXTRI_IRQ_Enable                      1


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// APIS
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void MCAL_EXTRI_GPIO_INIT(EXTRI_PinConfig_t *EXTRI_Config);
void MCAL_EXTRI_GPIO_Update(EXTRI_PinConfig_t *EXTRI_Config);
void MCAL_EXTRI_GPIO_DEINIT(void);

#endif /* EXTRI_H_ */