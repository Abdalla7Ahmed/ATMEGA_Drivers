/*
 * ATMEGA_Drivers.c
 *
 * Created: 03/12/2022 12:22:52 م
 * Author : Abdallah Ahmed
 */ 

#include <avr/io.h>
#include "MCAL/Includes/Include_MCAL_files.h"
//#define Tranmitter
#define Receiver
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
	LCD_INIT();
	USART_Config USART;
	USART.Interrupt_Enable = Interrupt_Enable_NONE;
//	USART.Interrupt_Enable = Interrupt_Enable_Complete_RX;
	//USART.P_IRQ_Callback =RX_ISR;
	USART.USART_Parity = USART_Parity_Even;
	USART.USART_PayLoad_Length = USART_PayLoad_Length_8Bits;
	USART.USART_Stop_Bit = USART_Stop_Bit_ONE;
	USART.USART_Mode = USART_Mode_Asynchronous;
	USART.USART_Baud_Rate = USART_Baud_Rate_9600;
	#ifdef Tranmitter
	USART.USART_Direction = USART_Direction_Transmitter;
	#endif
	#ifdef Receiver
	USART.USART_Direction = USART_Direction_Receiver;
	#endif
		
	MCAL_USART_Init(&USART);
	uint8_t *str1= "Abdallah#";
	uint8_t str2[20];
	uint8_t c=55;
	
	while(1)
	{
	#ifdef Tranmitter
	MCAL_USART_send_string(str1);
	#endif
	#ifdef Receiver
	MCAL_USART_receive_string(&str2,'#');
	LCD_WRITE_STRING(str2);
	LCD_clear_screen();
	#endif
	
	
	
		
	}
}

