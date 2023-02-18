/*
 * ATMEGA_Drivers.c
 *
 * Created: 03/12/2022 12:22:52 م
 * Author : Abdallah Ahmed
 */ 

#include <avr/io.h>
#include "MCAL/Includes/Include_MCAL_files.h"

void RX_ISR(void)
{
	uint16_t c;
	MCAL_USART_Receive_Data(&c,Disable_Polling);
	MCAL_USART_Send_data(&c,Enable_Polling);
	LCD_GOTO_XY(1,10);
	LCD_Send_A_Character(c);
}

int main(void)
{
	//LCD_INIT();
	//LCD_GOTO_XY(1,0);
	//LCD_WRITE_STRING("USART send ");
	USART_Config USART;
	USART.Interrupt_Enable = Interrupt_Enable_NONE;
//	USART.Interrupt_Enable = Interrupt_Enable_Complete_RX;
	//USART.P_IRQ_Callback =RX_ISR;
	USART.USART_Mode = USART_Mode_Asynchronous;
	USART.USART_Parity = USART_Parity_Disable;
	USART.USART_PayLoad_Length = USART_PayLoad_Length_8Bits;
	USART.USART_Stop_Bit = USART_Stop_Bit_ONE;
	USART.USART_Baud_Rate = USART_Baud_Rate_9600;
	USART.USART_Direction = USART_Direction_Transmitter_AND_Receiver;	
	MCAL_USART_Init(&USART);
	
	uint32_t number1=9658;
	uint8_t number[20];
	uint8_t str[20];
	uint8_t *str1 = "Abdallah ahmed";
	MCAL_USART_send_string(str1);
	MCAL_USART_send_number(&number1);
	while(1)
	{
		MCAL_USART_receive_string(&str,'#');
		MCAL_USART_send_string(&str);
		//MCAL_USART_receive_number(&number,'#');
		//MCAL_USART_send_string(&number);
		
	}
}

