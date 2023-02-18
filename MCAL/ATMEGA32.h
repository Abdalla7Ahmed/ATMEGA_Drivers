/*
 * ATMEGA32.h
 *
 * Created: 03/12/2022 02:10:11 PM
 *  Author: AbdallAH Ahmed Mohamed 
		  : ATMEGA base configuration
 */ 


#ifndef ATMEGA32_H_
#define ATMEGA32_H_

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>


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


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Base Addresses for Timer 
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define _TCCR0						    (*(volatile unsigned char*)(0x53))
#define _TCNT0							(*(volatile unsigned char*)(0x52))
#define _OCR0							(*(volatile unsigned char*)(0x5C))
#define _TIMSK						    (*(volatile unsigned char*)(0x59))
#define _TIFR							(*(volatile unsigned char*)(0x58))



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Base Addresses for Timer
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define _ADMUX						    (*(volatile unsigned char*)(0x27))
#define _ADCSRA							(*(volatile unsigned char*)(0x26))
#define _ADCH							(*(volatile unsigned char*)(0x25))
#define _ADCL						    (*(volatile unsigned char*)(0x24))
#define _SFIOR							(*(volatile unsigned char*)(0x50))

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Base Addresses for USART
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define _UDR						    (*(volatile unsigned char*)(0x2C))
#define _UCSRA  						(*(volatile unsigned char*)(0x2B))
#define _UCSRB							(*(volatile unsigned char*)(0x2A))
#define _UCSRC						    (*(volatile unsigned char*)(0x40))
#define _UBRRL							(*(volatile unsigned char*)(0x29))
#define _UBRRH							(*(volatile unsigned char*)(0x40))

#endif /* ATMEGA32_H_ */