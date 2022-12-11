/*
 * ATMEGA32.h
 *
 * Created: 03/12/2022 02:10:11 PM
 *  Author: AbdallAH Ahmed Mohamed 
		  : ATMEGA base configuration
 */ 


#ifndef ATMEGA32_H_
#define ATMEGA32_H_


// Direct Base Addresses for ATMEGA32
// Using these Macros Direct 
// two wire serial interfacing
#define TWBR_BASE							 *((volatile unsigned char *)(0x20))
#define TWSR_BASE							 *((volatile unsigned char *)(0x21))
#define TWAR_BASE							 *((volatile unsigned char *)(0x22))
#define TWDR_BASE							 *((volatile unsigned char *)(0x23))

// Analog to digital converter ADC
#define ADCL_BASE							 *((volatile unsigned char *)(0x24))
#define ADCH_BASE							 *((volatile unsigned char *)(0x25))
#define ADCSRA_BASE							 *((volatile unsigned char *)(0x26))
#define ADMUX_BASE							 *((volatile unsigned char *)(0x27))
#define ACSR_BASE							 *((volatile unsigned char *)(0x28))

// Universal Synchronous Asynchronous receiver transmitter (USART)
#define UBRRL_BASE							 *((volatile unsigned char *)(0x29))
#define USCRB_BASE						     *((volatile unsigned char *)(0x2A))
#define USCRA_BASE							 *((volatile unsigned char *)(0x2B))
#define UDR_BASE						     *((volatile unsigned char *)(0x2C))

// Serial Peripheral interface (SPI)
#define SPCR_BASE							 *((volatile unsigned char *)(0x2D))
#define SPSR_BASE						     *((volatile unsigned char *)(0x2E))
#define SPdR_BASE						     *((volatile unsigned char *)(0x2F))

// Input output registers (DIO)
#define PIND_BASE							 *((volatile unsigned char *)(0x30))
#define DDRD_BASE						     *((volatile unsigned char *)(0x31))
#define PORTD_BASE							 *((volatile unsigned char *)(0x32))
#define PINC_BASE							 *((volatile unsigned char *)(0x33))
#define DDRC_BASE						     *((volatile unsigned char *)(0x34))
#define PORTC_BASE							 *((volatile unsigned char *)(0x35))
#define PINB_BASE							 *((volatile unsigned char *)(0x36))
#define DDRB_BASE						     *((volatile unsigned char *)(0x37))
#define PORTB_BASE							 *((volatile unsigned char *)(0x38))
#define PINA_BASE							 *((volatile unsigned char *)(0x39))
#define DDRA_BASE						     *((volatile unsigned char *)(0x3A))
#define PORTA_BASE							 *((volatile unsigned char *)(0x3B))


// EEPROM
#define EECR_BASE							 *((volatile unsigned char *)(0x3C))
#define EEDR_BASE						     *((volatile unsigned char *)(0x3D))
#define EEARL_BASE							 *((volatile unsigned char *)(0x3E))
#define EEARH_BASE							 *((volatile unsigned char *)(0x3F))
#define UCSRC_BASE							 *((volatile unsigned char *)(0x40))
#define UBRRH_BASE							 *((volatile unsigned char *)(0x40))
#define WDTCR_BASE							 *((volatile unsigned char *)(0x41))
#define ASSR_BASE							 *((volatile unsigned char *)(0x42))
#define OCR2_BASE							 *((volatile unsigned char *)(0x43))

// Timer
#define TCNT2_BASE						     *((volatile unsigned char *)(0x44))
#define TCCR2_BASE						     *((volatile unsigned char *)(0x45))
#define ICR1L_BASE							 *((volatile unsigned char *)(0x46))
#define ICR1H_BASE						     *((volatile unsigned char *)(0x47))
#define OCR1BL_BASE							 *((volatile unsigned char *)(0x48))
#define OCR1BH_BASE						     *((volatile unsigned char *)(0x49))
#define OCR1AL_BASE							 *((volatile unsigned char *)(0x4A))
#define OCR1AH_BASE						     *((volatile unsigned char *)(0x4B))
#define TCNT1L_BASE						     *((volatile unsigned char *)(0x4C))
#define TCNT1H_BASE							 *((volatile unsigned char *)(0x4D))
#define TCCR1B_BASE						     *((volatile unsigned char *)(0x4E))
#define TCCR1A_BASE						     *((volatile unsigned char *)(0x4F))
#define SFIOR_BASE							 *((volatile unsigned char *)(0x50))
#define OCDR_BASE						     *((volatile unsigned char *)(0x51))
#define OSCCAL_BASE						     *((volatile unsigned char *)(0x51))
#define TCNT0_BASE							 *((volatile unsigned char *)(0x52))
#define TCCR0_BASE						     *((volatile unsigned char *)(0x53))
#define MCUCSR_BASE						     *((volatile unsigned char *)(0x54))
#define MCUCR_BASE							 *((volatile unsigned char *)(0x55))
#define TWCR_BASE						     *((volatile unsigned char *)(0x56))
#define SPMCR_BASE						     *((volatile unsigned char *)(0x57))
#define TIFR_BASE						     *((volatile unsigned char *)(0x58))
#define TIMSK_BASE						     *((volatile unsigned char *)(0x59))
#define GIFR_BASE							 *((volatile unsigned char *)(0x5A))
#define GICR_BASE							 *((volatile unsigned char *)(0x5B))
#define OCR0_BASE						     *((volatile unsigned char *)(0x5C))
#define SPL_BASE						     *((volatile unsigned char *)(0x5D))
#define SPH_BASE						     *((volatile unsigned char *)(0x5E))
#define SREG_BASE						     *((volatile unsigned char *)(0x5F))


// Base Addresses for DIOx
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


// Base Addresses for SPI registers
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



#endif /* ATMEGA32_H_ */