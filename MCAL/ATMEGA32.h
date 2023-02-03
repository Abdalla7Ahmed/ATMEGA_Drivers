/*
 * ATMEGA32.h
 *
 * Created: 03/12/2022 02:10:11 PM
 *  Author: AbdallAH Ahmed Mohamed 
		  : ATMEGA base configuration
 */ 


#ifndef ATMEGA32_H_
#define ATMEGA32_H_

#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Base Addresses for DIOx
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define DIOD_BASE	0x30
#define DIOC_BASE   0x33
#define DIOB_BASE   0x36
#define DIOA_BASE   0x39

typedef struct
{
	volatile unsigned char PINx  ;
	volatile unsigned char DDRx  ;
	volatile unsigned char PORTx ;
}Typdef_DIOx_t;

#define DIOA			((Typdef_DIOx_t *)DIOA_BASE)
#define DIOB			((Typdef_DIOx_t *)DIOB_BASE)
#define DIOC			((Typdef_DIOx_t *)DIOC_BASE)
#define DIOD			((Typdef_DIOx_t *)DIOD_BASE)



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Base Addresses for SPI registers
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define SPCR_BASE							 0x2D
#define SPSR_BASE						     0x2E
#define SPDR_BASE						     0x2F

typedef struct
{
	volatile unsigned char SPCR_m  ;
	volatile unsigned char SPSR_m  ;
	volatile unsigned char SPDR_m  ;
}Typdef_SPI_t;

#define SPI	            ((Typdef_SPI_t *)SPCR_BASE)



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Base Addresses for EXTRI registers
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define _MCUCR						    (*(volatile unsigned char*)(0x55))
#define _MCUCSR							(*(volatile unsigned char*)(0x54))
#define _GICR							(*(volatile unsigned char*)(0x5B))
#define _GIFR						    (*(volatile unsigned char*)(0x5A))
#define _SREG							(*(volatile unsigned char*)(0x5F))



#endif /* ATMEGA32_H_ */