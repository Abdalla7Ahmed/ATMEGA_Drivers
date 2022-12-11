/*
 * SPI.h
 *
 * Created: 11/12/2022 01:59:34 م
 *  Author: Abotaleb
 */ 


#ifndef SPI_H_
#define SPI_H_
//=====================Includes===========================
#include "ATMEGA32.h"
//========================================================

//=====================user type definitions===========================

typedef struct
{
	uint8_t SPI_interrupt	   ;     // the parameters must be set based on @ref SPI_Interrupt_define
	uint8_t SPI_Data_order     ;	 // the parameters must be set based on @ref SPI_Data_order_define
	uint8_t SPI_Direction	   ;	 // the parameters must be set based on @ref SPI_Dir_define
	uint8_t SPI_Mode		   ;	 // the parameters must be set based on @ref SPI_Mode_define
	uint8_t SPI_Clock_Rate	   ;	 // the parameters must be set based on @ref SPI_Clock_Rate_define

}SPI_PinConfig_t;


//========================================================

//@ref SPI_Interrupt_define
#define SPI_Interrupt_Enable                              1
#define SPI_Interrupt_Disable                             0

//========================================================
//@ref SPI_Data_order_define
#define SPI_Data_order_LSB								  1   // Least significant bit
#define SPI_Data_order_MSB								  0   // Most significant bit	

//========================================================
//@ref SPI_Dir_define
#define SPI_Dir_Master									  1   // set SPI as master
#define SPI_Dir_Slave 									  0	  // Set SPI as Slave

//========================================================
//@ref SPI_Mode_define
/*
Table 59. CPOL and CPHA Functionality
							Leading Edge			Trailing Edge			SPI Mode
CPOL = 0, CPHA = 0			Sample (Rising)			Setup (Falling)			0
CPOL = 0, CPHA = 1			Setup (Rising)			Sample (Falling)		1
CPOL = 1, CPHA = 0			Sample (Falling)		Setup (Rising)			2
CPOL = 1, CPHA = 1			Setup (Falling)			Sample (Rising)			3
*/
#define SPI_Mode_0											0
#define SPI_Mode_1											1
#define SPI_Mode_2											2
#define SPI_Mode_3											3

//========================================================
//@ref SPI_Clock_Rate_define
/*
SPI2X			SPR1			SPR0			SCK Frequency
0				0				0				fosc/4
0				0				1				fosc/16
0				1				0				fosc/64
0				1				1				fosc/128
1				0				0				fosc/2
1				0				1				fosc/8
1				1				0				fosc/32
1				1				1				fosc/64
*/
#define SPI_Clock_Rate_Fosc_D4							   0
#define SPI_Clock_Rate_Fosc_D16							   1
#define SPI_Clock_Rate_Fosc_D64							   2
#define SPI_Clock_Rate_Fosc_D128						   3
#define SPI_Clock_Rate_D_Fosc_D4						   4
#define SPI_Clock_Rate_D_Fosc_D16						   5
#define SPI_Clock_Rate_D_Fosc_D64						   6
#define SPI_Clock_Rate_D_Fosc_D128						   7

//======================== General Macros =========================
// register SPCR
#define SPR0_m											   ((unsigned char)0x01U) // 0b0000 0001				
#define SPR1_m											   ((unsigned char)0x02U) // 0b0000 0010	
#define CPHA_m											   ((unsigned char)0x04U) // 0b0000 0100
#define CPOL_m											   ((unsigned char)0x08U) // 0b0000 1000
#define MSTR_m											   ((unsigned char)0x10U) // 0b0001 0000
#define DORD_m											   ((unsigned char)0x20U) // 0b0010 0000	
#define SPE_m											   ((unsigned char)0x40U) // 0b0100 0000		
#define SPIE_m										       ((unsigned char)0x80U) // 0b1000 0000

// register SPSR
#define SPI2X_m										       ((unsigned char)0x01U) // 0b0000 0001
#define WCOL_m											   ((unsigned char)0x40U) // 0b0100 0000
#define SPIF_m											   ((unsigned char)0x80U) // 0b0000 0001

#define Wait_Transmition_complete()						   while(!(SPI->SPSR_m)&(1<<7))

//========================Pins configuration ===============
#define MOSI												5
#define MISO												6
#define SCK													7
#define SS													4

//====================== APIS ============================
void MCAL_SPI_init(Typdef_SPI_t *SPI_m,SPI_PinConfig_t *pinCinfig);
void MCAL_SPI_send_Data(Typdef_SPI_t *SPI_m,uint8_t Data);
uint8_t MCAL_SPI_Receive_Data(Typdef_SPI_t *SPI_m);
uint8_t MCAL_SPI_send_Receive_Data(Typdef_SPI_t *SPI_m,uint8_t Data);








#endif /* SPI_H_ */