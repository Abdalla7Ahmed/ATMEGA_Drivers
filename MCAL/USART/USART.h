/*
 * USART.h
 *
 * Created: 03/02/2023 03:57:40 م
 *  Author: Abotaleb
 */ 


#ifndef USART_H_
#define USART_H_

#include "Include_MCAL_files.h"
#define F_CPU 8000000UL
typedef struct 
{
	uint8_t  Interrupt_Enable	  ;	// must set by @ref Interrupt_Enable_define 
	uint8_t  USART_Direction	  ;	// must set by @ref USART_Direction_define
	uint8_t  USART_Mode			  ;	// must set by @ref USART_Mode_define
	uint8_t  USART_Parity		  ;	// must set by @ref USART_Parity_define
	uint8_t  USART_Stop_Bit       ;	// must set by @ref USART_Stop_Bit_define
	uint8_t  USART_PayLoad_Length ;	// must set by @ref USART_PayLoad_Length_define
	uint8_t  USART_Clock_Polarity ; // must set by @ref USART_Clock_Polarity_define
	uint8_t  USART_Speed_State    ;	// must set by @ref USART_Speed_State_define
	uint16_t USART_Baud_Rate      ;	// must set by @ref USART_Baud_Rate_define
	void(* P_IRQ_Callback)(void)  ; 
}USART_Config;	







//@ref Interrupt_Enable_define
#define Interrupt_Enable_NONE							(uint8_t)(0x0)		
#define Interrupt_Enable_Complete_TX					(uint8_t)(1<<6)
#define Interrupt_Enable_Complete_RX					(uint8_t)(1<<7)
#define Interrupt_Enable_UDR_Empty						(uint8_t)(1<<5)
#define Interrupt_Enable_UDR_AND_TX						(uint8_t)( (1<<5) |(1<<6) )
#define Interrupt_Enable_UDR_AND_RX						(uint8_t)( (1<<5) |(1<<7) )
#define Interrupt_Enable_TX_AND_RX						(uint8_t)( (1<<6) |(1<<7) )
#define Interrupt_Enable_TX_AND_RX_AND_UDR				(uint8_t)( (1<<5) |(1<<6) | (1<<7) )





//@ref USART_Direction_define
#define USART_Direction_Transmitter						(uint8_t)(1<<3)
#define USART_Direction_Receiver						(uint8_t)(1<<4)
#define USART_Direction_Transmitter_AND_Receiver		(uint8_t)( (1<<3) | (1<<4) )



//@ref USART_Mode_define
#define USART_Mode_Asynchronous							(uint8_t)(0x0)
#define USART_Mode_Synchronous							(uint8_t)(1<<6)
	
	

//@ref USART_Parity_define

#define USART_Parity_Disable							(uint8_t)(0x0)
#define USART_Parity_Even								(uint8_t)(1<<5)
#define USART_Parity_Odd								(uint8_t)( (1<<5) | (1<<4))

//@ref USART_Stop_Bit_define	
#define USART_Stop_Bit_ONE								(uint8_t)(0x0)
#define USART_Stop_Bit_TWO								(uint8_t)(1<<3)
	


//@ref USART_PayLoad_Length_define

#define USART_PayLoad_Length_5Bits						(uint8_t)(0x0)
#define USART_PayLoad_Length_6Bits						(uint8_t)(1<<1)
#define USART_PayLoad_Length_7Bits						(uint8_t)(1<<2)
#define USART_PayLoad_Length_8Bits						(uint8_t)( (1<<1) | (1<<2))
#define USART_PayLoad_Length_9Bits						(uint8_t)(0xA)	


//@ref USART_Clock_Polarity_define
#define USART_Clock_Polarity_TXRising_AND_RXFalling	    (uint8_t)(0x0)
#define USART_Clock_Polarity_RXRising_AND_TXFalling		(uint8_t)(0x0)

//@ref USART_Speed_State_define
#define USART_Speed_State_Normal_Speed					(uint8_t)(0x0)
#define USART_Speed_State_Double_Speed					(uint8_t)(1<<1)  // set U2x bit to double the speed

//@ref USART_Baud_Rate_define
#define USART_Baud_Rate_2400						    (uint16_t)(416) 
#define USART_Baud_Rate_4800						    (uint8_t )(207)
#define USART_Baud_Rate_9600						    (uint8_t )(103)
#define USART_Baud_Rate_14400						    (uint8_t )(68)
#define USART_Baud_Rate_19200						    (uint8_t )(51)
#define USART_Baud_Rate_28800						    (uint8_t )(34)
#define USART_Baud_Rate_38400						    (uint8_t )(25)
#define USART_Baud_Rate_57600						    (uint8_t )(16)
#define USART_Baud_Rate_76800						    (uint8_t )(12)
#define USART_Baud_Rate_115200						    (uint8_t )(8)
#define USART_Baud_Rate_230400						    (uint8_t )(3)
#define USART_Baud_Rate_250000						    (uint8_t )(3)
#define USART_Baud_Rate_500000						    (uint8_t )(1)




typedef enum 
{
	Enable_Polling,
	Disable_Polling
}Polling_State_t;

typedef enum
{
	Flag_Reset,
	Flag_SET
}Flage_State;

typedef enum
{
	_RXC  ,	/*USART Receive Complete*/
	_TXC  ,	/*USART Transmit Complete*/
	_UDRE ,	/*USART Data Register Empty*/
	_FE   ,	/*Frame Error*/
	_DOR  ,	/*Data OverRun*/	
	_PE		/*Parity Error*/	
}Status;

typedef struct 
{
	uint8_t Frame_Erro:1;
	uint8_t Data_OverRun :1 ;
	uint8_t Parity_Error :1;
	uint8_t Reserved :5;
}Flags_Error;

// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// *==================== APIS ==========================*
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

void MCAL_USART_Init(USART_Config *USART_Configuration);
void MCAL_USART_Deinit(void);
void MCAL_USART_Send_data(uint16_t *TxBuffer,Polling_State_t Polling_state);
Flags_Error MCAL_USART_Receive_Data(uint16_t *RxBuffer,Polling_State_t Polling_state);
Flags_Error MCAL_USART_Send_AND_Receive_Data(uint16_t *Buffer,Polling_State_t Polling_state);
void MCAL_USART_send_string(uint8_t *string);
void MCAL_USART_send_number(uint32_t *number);
void MCAL_USART_receive_string(uint8_t *buffer,uint8_t defaultStop);
void MCAL_USART_receive_number(uint8_t *number,uint8_t defaultStop);
Flage_State USART_Get_Flag_State(Status Flag);

	
	
#endif /* USART_H_ */