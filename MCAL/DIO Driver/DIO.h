/*
 * DIO.h
 *
 * Created: 03/12/2022 12:27:25 م
 *  Author: Abotaleb
 */ 


#ifndef DIO_H_
#define DIO_H_


//=====================Includes===========================
#include "ATMEGA32.h"
//========================================================

//=====================user type definitions===========================

typedef struct
{
	// specified DIO pin number to be configured
	// the parameters must be set based on @ref DIO_PIN_define
	uint8_t DIO_PinNumber ;  
	// specified DIO mood to be configured
	// the parameters must be set based on @ref DIO_Mood_define                     
	uint8_t DIO_Mood	  ;
}DIO_PinConfig_t;


//========================================================
//@ref DIO_PIN_define
#define DIO_PIN_0             ((unsigned char)0x01U) // pin 0      0b0000 0001
#define DIO_PIN_1             ((unsigned char)0x02U) // pin 1      0b0000 0010
#define DIO_PIN_2             ((unsigned char)0x04U) // pin 2      0b0000 0100
#define DIO_PIN_3             ((unsigned char)0x08U) // pin 3      0b0000 1000
#define DIO_PIN_4             ((unsigned char)0x10U) // pin 4      0b0001 0000
#define DIO_PIN_5             ((unsigned char)0x20U) // pin 5      0b0010 0000
#define DIO_PIN_6             ((unsigned char)0x40U) // pin 6      0b0100 0000
#define DIO_PIN_7             ((unsigned char)0x80U) // pin 7      0b1000 0000
#define DIO_PINS_All          ((unsigned char)0xFFU) // all pins   0b1111 1111

//========================================================

#define DIO_Mood_Input_HIZ						 0
#define DIO_Mood_Input_PU						 1	
#define DIO_Mood_Output							 2

//========================================================

//@ref DIO_Mood_define 
#define DIO_PIN_Low						0
#define DIO_PIN_High					1


//====================== APIS ============================
void MCAL_DIO_init(Typdef_DIOx_t *DIOx,DIO_PinConfig_t *DIO_config);
void MCAL_DIO_init_PORT(Typdef_DIOx_t *DIOx,DIO_PinConfig_t *DIO_config);
void MCAL_DIO_Deinit(Typdef_DIOx_t *DIOx);
void MCAL_DIO_Write_pin(Typdef_DIOx_t *DIOx,uint8_t Pin_number,uint8_t value);
void MCAL_DIO_Write_Port(Typdef_DIOx_t *DIOx,uint8_t value);
uint8_t MCAL_DIO_Read_Pin(Typdef_DIOx_t *DIOx,uint8_t Pin_number);
uint8_t MCAL_DIO_Read_Port(Typdef_DIOx_t *DIOx);
void MCAL_DIO_Toggle_Pin(Typdef_DIOx_t *DIOx,uint8_t Pin_number);
void MCAL_DIO_Toggle_Port(Typdef_DIOx_t *DIOx);
#endif /* DIO_H_ */