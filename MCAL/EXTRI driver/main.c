/*
 * ATMEGA_Drivers.c
 *
 * Created: 03/12/2022 12:22:52 م
 * Author : Abdallah Ahmed
 */ 

#include <avr/io.h>
#include "MCAL/Includes/Include_MCAL_files.h"

void EXTRI_callback_0(void);
void EXTRI_callback_1(void);
void EXTRI_callback_2(void);	
void DIO_configuration(void);
void EXTRI_configuration(void);



DIO_PinConfig_t DIO_pin;
EXTRI_PinConfig_t EXTRI_pin;

int main(void)
{
	//DIO configuration 
	DIO_configuration();
	
	// EXTRI configuration
	EXTRI_configuration();
	
	while(1)
	{
		// Reset all LEd
		MCAL_DIO_Write_pin(DIOD,DIO_PIN_5,DIO_PIN_Low);
		MCAL_DIO_Write_pin(DIOD,DIO_PIN_6,DIO_PIN_Low);
		MCAL_DIO_Write_pin(DIOD,DIO_PIN_7,DIO_PIN_Low);
	}
}

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

void EXTRI_callback_0(void)
{
	MCAL_DIO_Write_pin(DIOD,DIO_PIN_5,DIO_PIN_High);
	_delay_ms(1000);
}
void EXTRI_callback_1(void)
{
	MCAL_DIO_Write_pin(DIOD,DIO_PIN_6,DIO_PIN_High);
	_delay_ms(1000);
}
void EXTRI_callback_2(void)
{
	MCAL_DIO_Write_pin(DIOD,DIO_PIN_7,DIO_PIN_High);
	_delay_ms(1000);
}

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
void DIO_configuration(void)
{
	// set pin 5 in PORTD as an output
	DIO_pin.DIO_PinNumber = DIO_PIN_5;
	DIO_pin.DIO_Mood 	  = DIO_Mood_Output;
	MCAL_DIO_init(DIOD,&DIO_pin);
	
	// set pin 6 in PORTD as an output
	DIO_pin.DIO_PinNumber = DIO_PIN_6;
	DIO_pin.DIO_Mood 	  = DIO_Mood_Output;
	MCAL_DIO_init(DIOD,&DIO_pin);
	
	// set pin 7 in PORTD as an output
	DIO_pin.DIO_PinNumber = DIO_PIN_7;
	DIO_pin.DIO_Mood 	  = DIO_Mood_Output;
	MCAL_DIO_init(DIOD,&DIO_pin);
}
// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
void EXTRI_configuration()
{
	
	// External Interrupt 0 (INT0)-PD2. >> irqoccur when “any logical change”
	EXTRI_pin.EXTRI_Number   = EXTI_0;
	EXTRI_pin.EXTRI_Case     = EXTRI_Trigger_RisingANDFailing;
	EXTRI_pin.IRQ_ENABLE     = EXTRI_IRQ_Enable;
	EXTRI_pin.P_IRQ_CallBack = EXTRI_callback_0;
	MCAL_EXTRI_GPIO_INIT(&EXTRI_pin);
	
	//External Interrupt 1 (INT1)-PD3. >> irqoccur when “rising edge”
	EXTRI_pin.EXTRI_Number   = EXTI_1;
	EXTRI_pin.EXTRI_Case     = EXTRI_Trigger_Rising;
	EXTRI_pin.IRQ_ENABLE     = EXTRI_IRQ_Enable;
	EXTRI_pin.P_IRQ_CallBack = EXTRI_callback_1;
	MCAL_EXTRI_GPIO_INIT(&EXTRI_pin);
	
	//External Interrupt 2 (INT2)-PB2. >> irqoccur when “Falling edge”
	EXTRI_pin.EXTRI_Number   = EXTI_2;
	EXTRI_pin.EXTRI_Case 	 = EXTRI_Trigger_Failing;
	EXTRI_pin.IRQ_ENABLE 	 = EXTRI_IRQ_Enable;
	EXTRI_pin.P_IRQ_CallBack = EXTRI_callback_2;
	MCAL_EXTRI_GPIO_INIT(&EXTRI_pin);
	
}
// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
