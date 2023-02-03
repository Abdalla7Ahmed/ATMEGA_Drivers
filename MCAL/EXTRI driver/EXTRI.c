/*
 * EXTRI.c
 *
 * Created: 31/01/2023 07:43:19 م
 *  Author: Abotaleb
 */ 

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Includes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "includes/EXTRI.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Macros
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
 

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Variables
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void(* GP_IRQ_CallBack[3])(void);

/**================================================================
 * @Fn		  - MCAL_EXTRI_GPIO_INIT
 * @brief 	  - initialize the EXTRI 
 * @param[in] - EXTRI_Config Set by @ref EXTRI_define , EXTRI_Trigger_define and EXTRI_IRQ_define
 * @retval	  - none
 * Note		  - INT0 and INt1 can be low level interrupt , any logic change interrupt , 
				rising trigger interrupt or failing trigger interrupt but 
				INT2 can only be rising or failing interrupt 
================================================================**/	

void MCAL_EXTRI_GPIO_INIT(EXTRI_PinConfig_t *EXTRI_Config)
{
	if ((EXTRI_Config->EXTRI_Number == EXTI_0) || (EXTRI_Config->EXTRI_Number == EXTI_1) )
	{
		/*
		ISC(11/01) 		 ISC(10/00)		 Description
		0				 0				 The low level of INT0 generates an interrupt request.
		0				 1		  	     Any logical change on INT0 generates an interrupt request.
		1				 0				 The falling edge of INT0 generates an interrupt request.
		1				 1				 The rising edge of INT0 generates an interrupt request.
		*/
		
	    switch (EXTRI_Config ->EXTRI_Case)
		{
			case EXTRI_Trigger_Lowlevel:
				_MCUCR |=((EXTRI_Config->EXTRI_Number) == EXTI_0) ? EXTRI_Trigger_Lowlevel:(EXTRI_Trigger_Lowlevel<<2);
				break;
			case EXTRI_Trigger_RisingANDFailing:
				_MCUCR |=((EXTRI_Config->EXTRI_Number) == EXTI_0) ? EXTRI_Trigger_RisingANDFailing:(EXTRI_Trigger_RisingANDFailing<<2);
				break;
			case EXTRI_Trigger_Failing:
				_MCUCR |=((EXTRI_Config->EXTRI_Number) == EXTI_0) ? EXTRI_Trigger_Failing:(EXTRI_Trigger_Failing<<2);
				break;
			case EXTRI_Trigger_Rising:
				_MCUCR |=((EXTRI_Config->EXTRI_Number) == EXTI_0) ? EXTRI_Trigger_Rising:(EXTRI_Trigger_Rising<<2);
				break;
		}
		if (EXTRI_Config->EXTRI_Number == EXTI_0)
		{
			_GICR |=(1<<6);
		}
		else if (EXTRI_Config->EXTRI_Number == EXTI_1)
		{
			_GICR |=(1<<7);
		}
	}
	// INT2 can be only rising or failing edge
	else if (EXTRI_Config->EXTRI_Number == EXTI_2)
	{
		if (EXTRI_Config->EXTRI_Case ==EXTRI_Trigger_Failing)
		{
			_MCUCSR &=~(1<<6);
		}
		else if (EXTRI_Config->EXTRI_Case ==EXTRI_Trigger_Rising)
		{
			_MCUCSR |=(1<<6);
		}
	    _GICR |=(1<<5);
	}
	// call back function 
	GP_IRQ_CallBack[EXTRI_Config->EXTRI_Number]=EXTRI_Config->P_IRQ_CallBack;
	// Enable interrupt 
	if(EXTRI_Config ->IRQ_ENABLE == EXTRI_IRQ_Enable)
	{
		//sei();
		_SREG |= (1<<7);
	}
 	else if (EXTRI_Config ->IRQ_ENABLE == EXTRI_IRQ_Disable)
 	{
 		cli();
 	}
}

/**================================================================
 * @Fn		  - MCAL_EXTRI_GPIO_DEINIT
 * @brief 	  - Reset the EXTRI registers
 * @param[in] - none
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_EXTRI_GPIO_DEINIT(void)
{
	_MCUCR		= 0x00;							
	_MCUCSR		= 0x00;				
	_GICR		= 0x00;			
	_GIFR		= 0x00;					
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// IRQ Functions
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

ISR(INT0_vect)
{
	GP_IRQ_CallBack[0]();
}
ISR(INT1_vect)
{
	GP_IRQ_CallBack[1]();
}
ISR(INT2_vect)
{
	GP_IRQ_CallBack[2]();
}