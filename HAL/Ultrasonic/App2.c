/*
 * ATMEGA_Drivers.c
 *
 * Created: 03/12/2022 12:22:52 م
 * Author : Abdallah Ahmed
 */ 

#include <avr/io.h>
#include "MCAL/Includes/Include_MCAL_files.h"
#include "HAL/Includes/Include_HAL_Files.h"
void IRQ1_callback(void)
{
	PORTA = 0x1;
}

void IRQ2_callback()
{
	PORTA = 0x0;
}
int main(void)
{

	USART_Config USART;
	USART.Interrupt_Enable = Interrupt_Enable_NONE;
	//	USART.Interrupt_Enable = Interrupt_Enable_Complete_RX;
	//USART.P_IRQ_Callback =RX_ISR;
	USART.USART_Mode = USART_Mode_Asynchronous;
	USART.USART_Parity = USART_Parity_Disable;
	USART.USART_PayLoad_Length = USART_PayLoad_Length_8Bits;
	USART.USART_Stop_Bit = USART_Stop_Bit_ONE;
	USART.USART_Baud_Rate = USART_Baud_Rate_9600;
	USART.USART_Direction = USART_Direction_Transmitter;
	MCAL_USART_Init(&USART);

	Ultrasonic_Init();
	
	uint8_t d;
	while(1)
	{
		HAL_Ultrasonic_Start(DIO_PIN_0);
		if(HAL_Ultrasonic_Get_Distansc(&d))
		{
			LCD_GOTO_XY(0,0);
			LCD_display_number(d);
		}
		MCAL_USART_send_string("  Ultrasonic Distance is : ");
		MCAL_USART_send_number(&d);

	}
}

