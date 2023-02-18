/*
 * USART.c
 *
 * Created: 03/02/2023 03:57:24 PM
 *  Author: Abdallah Ahmed Mohamed 
 */ 


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Includes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "Includes/USART.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Macros
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*3


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Variables
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


USART_Config G_USART_Config ;
DIO_PinConfig_t DIO_PIN;
void(* G_USART_TX_Complete_CallBack)(void);
void(* G_USART_RX_Complete_CallBack)(void);
void(* G_USART_UDR_EMPTY_CallBack)(void);

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Generic Functions
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
 

Flage_State USART_Get_Flag_State(Status Flag)
{
	Flage_State Bit_Stat;
	
	Bit_Stat = Flag_Reset;
	switch(Flag)
	{
		case _RXC:
			Bit_Stat = (_UCSRA &(1<<7))?Flag_SET:Flag_Reset;
			break;
		case _TXC:
			Bit_Stat = (_UCSRA &(1<<6))?Flag_SET:Flag_Reset;
			break;
		case _UDRE:
			Bit_Stat = (_UCSRA &(1<<5))?Flag_SET:Flag_Reset;
			break;
		case _FE:
			Bit_Stat = (_UCSRA &(1<<4))?Flag_SET:Flag_Reset;
			break;
		case _DOR:
			Bit_Stat = (_UCSRA &(1<<3))?Flag_SET:Flag_Reset;
			break;
		case _PE:
			Bit_Stat = (_UCSRA &(1<<2))?Flag_SET:Flag_Reset;
			break;
	}
	return Bit_Stat;
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// APIS implement
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


/**================================================================
 * @Fn		  - MCAL_USART_Init
 * @brief 	  - initialize the USART  
 * @param[in] - USART_Config
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_USART_Init(USART_Config *USART_Configuration)
{
	G_USART_Config = *USART_Configuration;
	uint8_t Bouad_rate =0;
	
	_UCSRA |= USART_Configuration->USART_Speed_State;
	
	// USART Direction
	_UCSRB |= USART_Configuration->USART_Direction;
	
	
	// make URSEL reading UCSRC not UBRRH   by default = 1
	_UCSRC |= 1<<7;
	
	// USARt mode
	_UCSRC |=USART_Configuration->USART_Mode;
	
	//parity Check 
	_UCSRC |=USART_Configuration->USART_Parity;
	
	// number of stop bits
	_UCSRC |=USART_Configuration->USART_Stop_Bit;
	
	// the number of bits in frame 
	if( (USART_Configuration->USART_PayLoad_Length) == USART_PayLoad_Length_9Bits)
	{
		_UCSRB |=1<<2;
		_UCSRC |=1<<1;
		_UCSRC |=1<<2;
	}
	else 
	{
		_UCSRC |=USART_Configuration->USART_PayLoad_Length;
	}
	
	if( (USART_Configuration->USART_Mode) == USART_Mode_Synchronous)
	{
		if (USART_Configuration->USART_Direction == USART_Direction_Transmitter)
		{
			DIO_PIN.DIO_Mood = DIO_Mood_Output;
			DIO_PIN.DIO_PinNumber = DIO_PIN_0;
			MCAL_DIO_init(DIOB,&DIO_PIN);
		}
		else if (USART_Configuration->USART_Direction == USART_Direction_Receiver)
		{
			DIO_PIN.DIO_Mood = DIO_Mood_Input_HIZ;
			DIO_PIN.DIO_PinNumber = DIO_PIN_0;
			MCAL_DIO_init(DIOB,&DIO_PIN);
		}
		_UCSRC |=USART_Configuration->USART_Clock_Polarity;
	}
	
	
	
	// Baud rate 
	if( USART_Configuration->USART_Mode == USART_Mode_Asynchronous )
	{	
		if( (USART_Configuration->USART_Speed_State) == USART_Speed_State_Double_Speed)  
		{
			
			// make URSEL reading UBRRH not UCSRC
			_UBRRH &= ~(1<<7);
			_UBRRL = (uint8_t)(USART_Configuration->USART_Baud_Rate);
			_UBRRH = (USART_Configuration->USART_Baud_Rate) >>8 ;
		
		}
		else 
		{
			Bouad_rate = (USART_Configuration->USART_Baud_Rate) /2 ; 
			_UBRRL = Bouad_rate;
		}
		
	}	
	
	
	// the interrupt state
	if( (USART_Configuration->Interrupt_Enable) != Interrupt_Enable_NONE)
	{
		// Enable the general interrupt 
		_SREG |= (1<<7);
		
		_UCSRB |= USART_Configuration->Interrupt_Enable;   
		if( (USART_Configuration->Interrupt_Enable) == Interrupt_Enable_Complete_RX)
		{
			G_USART_RX_Complete_CallBack = USART_Configuration->P_IRQ_Callback;
		}
		if( (USART_Configuration->Interrupt_Enable) == Interrupt_Enable_Complete_TX)
		{
			G_USART_TX_Complete_CallBack = USART_Configuration->P_IRQ_Callback;
		}
		if( (USART_Configuration->Interrupt_Enable) == Interrupt_Enable_UDR_Empty)
		{
			G_USART_UDR_EMPTY_CallBack	 = USART_Configuration->P_IRQ_Callback;
		}
		
	}
	
}

/**================================================================
 * @Fn		  - MCAL_USART_Deinit
 * @brief 	  - Deinit the USART 
 * @param[in] - none
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_USART_Deinit(void)
{
	_UCSRA |=  (1<<6); // clear TXC by writing one in this bit 
	_UCSRA &= ~(1<<1);
	_UCSRA &= ~(1<<0);
	_UCSRB &=  (0x02); // RXB8 is read only bit  
	_UCSRC &= ~(1<<6);
	_UCSRC &= ~(1<<5);
	_UCSRC &= ~(1<<4);
	_UCSRC &= ~(1<<3);
	_UCSRC &= ~(1<<0);
	_UBRRL  =  (0x00);
	_UBRRH  =  (0x00);
	
}
/**================================================================
 * @Fn		  - MCAL_USART_Send_data
 * @brief 	  - send the buffer from USART 
 * @param[in] - pointer to the TXbuffer
 * @param[in] - Polling State
 * @retval	  - flags value
 * Note		  - none
================================================================**/	
uint8_t MCAL_USART_Send_data(uint16_t *TxBuffer,Polling_State_t Polling_state)
{
	if(Polling_state != Disable_Polling)
	{
		while(! USART_Get_Flag_State(_UDRE));
	}
	if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_9Bits)
	{
		if( (*TxBuffer)&0x100 )
		{
			_UCSRB  |= 1<<0;
		}
		_UDR = (*TxBuffer & (uint8_t)0xFF);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_8Bits)
	{
		_UDR = (*TxBuffer & (uint8_t)0xFF);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_7Bits)
	{
		_UDR = (*TxBuffer & (uint8_t)0x7F);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_6Bits)
	{
		_UDR = (*TxBuffer & (uint8_t)0x3F);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_5Bits)
	{
		_UDR = (*TxBuffer & (uint8_t)0x1F);
	}
	uint8_t Flags=0;
	Flags = (_UCSRA & 0xFC);
	return Flags;
}

/**================================================================
 * @Fn		  - MCAL_USART_Receive_Data
 * @brief 	  - Receive the buffer to USART  
 * @param[in] - pointer to the RxBuffer
 * @param[in] - Polling State
 * @retval	  - flags value
 * Note		  - none
================================================================**/	
uint8_t MCAL_USART_Receive_Data(uint16_t *RxBuffer,Polling_State_t Polling_state)
{
	uint8_t MSB =0;
	if(Polling_state != Disable_Polling)
	{
		while(! USART_Get_Flag_State(_RXC));
	}
	if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_9Bits)
	{
		if( (_UCSRB)&0x100 )
		{
			MSB = (_UCSRB & (1<<1) )>>1;
		}
		*((uint16_t*) RxBuffer) = (uint16_t)(_UDR | (MSB <<8));
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_8Bits)
	{
		*((uint16_t*) RxBuffer) = (_UDR &(uint8_t)0xFF);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_7Bits)
	{
		*((uint16_t*) RxBuffer) = (_UDR &(uint8_t)0x7F);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_6Bits)
	{
		*((uint16_t*) RxBuffer) = (_UDR &(uint8_t)0x3F);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_5Bits)
	{
		*((uint16_t*) RxBuffer) = (_UDR &(uint8_t)0x1F);
	}
	uint8_t Flags=0;
	Flags = (_UCSRA & 0xFC);
	return Flags;
}

/**================================================================
 * @Fn		  - MCAL_USART_Send_AND_Receive_Data
 * @brief 	  - Send the current buffer and then Receive the new buffer 
 * @param[in] - pointer to the RxBuffer
 * @param[in] - Polling State
 * @retval	  - flags value
 * Note		  - none
================================================================**/	
uint8_t MCAL_USART_Send_AND_Receive_Data(uint16_t *Buffer,Polling_State_t Polling_state)
{
	uint8_t MSB =0;
	// send the current buffer
	if(Polling_state != Disable_Polling)
	{
		while(! USART_Get_Flag_State(_UDR));
	}
	if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_9Bits)
	{
		if( (*Buffer)&0x100 )
		{
			_UCSRB  |= 1<<0;
		}
		_UDR = (*Buffer & (uint8_t)0xFF);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_8Bits)
	{
		_UDR = (*Buffer & (uint8_t)0xFF);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_7Bits)
	{
		_UDR = (*Buffer & (uint8_t)0x7F);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_6Bits)
	{
		_UDR = (*Buffer & (uint8_t)0x3F);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_5Bits)
	{
		_UDR = (*Buffer & (uint8_t)0x1F);
	}
	// Receive the new buffer
	
	if(Polling_state != Disable_Polling)
	{
		while(! USART_Get_Flag_State(_RXC));
	}
	if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_9Bits)
	{
		if( (_UCSRB)&0x100 )
		{
			MSB = (_UCSRB & (1<<1) )>>1;
		}
		*((uint16_t*) Buffer) = (uint16_t)(_UDR | (MSB <<8));
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_8Bits)
	{
		*((uint16_t*) Buffer) = (_UDR &(uint8_t)0xFF);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_7Bits)
	{
		*((uint16_t*) Buffer) = (_UDR &(uint8_t)0x7F);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_6Bits)
	{
		*((uint16_t*) Buffer) = (_UDR &(uint8_t)0x3F);
	}
	else if( (G_USART_Config.USART_PayLoad_Length) == USART_PayLoad_Length_5Bits)
	{
		*((uint16_t*) Buffer) = (_UDR &(uint8_t)0x1F);
	}
	uint8_t Flags=0;
	Flags = (_UCSRA & 0xFC);
	return Flags;
}
/**================================================================
 * @Fn		  - MCAL_USART_send_string
 * @brief 	  - Send string 
 * @param[in] - pointer to the string
 * @param[in] - none
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_USART_send_string(uint8_t *string)
{
	uint8_t i=0;
	while(string[i] !=0)  MCAL_USART_Send_data(&string[i++],Enable_Polling);
}

/**================================================================
 * @Fn		  - MCAL_USART_send_number
 * @brief 	  - Send string 
 * @param[in] - pointer to the number
 * @param[in] - none
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_USART_send_number(uint32_t *number)
{
	uint8_t counter=0;
	uint8_t number_array[10];
	while((*number) != 0)
	{
		number_array[counter] = ((*number)%10) +'0';
		(*number) /=10;
		counter ++;
	}
	for(int i=counter-1;i>=0;i--)
	{
		MCAL_USART_Send_data(&number_array[i],Enable_Polling);
	}
	
}
/**================================================================
 * @Fn		  - MCAL_USART_receive_string
 * @brief 	  - Receive string 
 * @param[in] - pointer to the string
 * @param[in] - defaultStop 
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_USART_receive_string(uint8_t *buffer,uint8_t defaultStop)
{
	uint8_t i=0;
	MCAL_USART_Receive_Data(&buffer[i],Enable_Polling);
	while(buffer[i] != defaultStop)
	{
		i++;
		MCAL_USART_Receive_Data(&buffer[i],Enable_Polling);
	}
	buffer[i] ='\0';
}
/**================================================================
 * @Fn		  - MCAL_USART_receive_number
 * @brief 	  - Receive number 
 * @param[in] - pointer to the number
 * @param[in] - defaultStop 
 * @retval	  - none
 * Note		  - none
================================================================**/	
void MCAL_USART_receive_number(uint8_t *number,uint8_t defaultStop)
{
	uint32_t counter=0;
	MCAL_USART_Receive_Data(&number[counter],Enable_Polling);
	while(number[counter]!=defaultStop)
	{
		counter ++;
		MCAL_USART_Receive_Data(&number[counter],Enable_Polling);
	}
	number[counter] = '\0';
}



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// ISR
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

/* USART Data Register Empty */
ISR(USART_RXC_vect)
{
	G_USART_RX_Complete_CallBack();
	
}
/* USART Data Register Empty */
ISR(USART_UDRE_vect)
{
	
 G_USART_UDR_EMPTY_CallBack();	
	
}
/* USART, Tx Complete */
ISR(USART_TXC_vect)
{
	G_USART_TX_Complete_CallBack();
	
}
	