/*
 * SPI.c
 *
 * Created: 11/12/2022 01:59:24 PM
 *  Author: Abdallah Ahmed
 */ 

#include "Includes/SPI.h"
#include "Includes/DIO.h"

// ============================= General Pointers=========================


// ============================= Inner Functions=========================
void SPI_Pins_Master_init(void)
{
	DIO_PinConfig_t pin;
	
	// slave select
	pin.DIO_PinNumber = DIO_PIN_4;
	pin.DIO_Mood = DIO_Mood_Output;
	MCAL_DIO_init(DIOB,&pin);
	
	// MOSI Master output Slave Input
	pin.DIO_PinNumber = DIO_PIN_5;
	pin.DIO_Mood = DIO_Mood_Output;
	MCAL_DIO_init(DIOB,&pin);
	
	// SCK   clock
	pin.DIO_PinNumber = DIO_PIN_7;
	pin.DIO_Mood = DIO_Mood_Output;
	MCAL_DIO_init(DIOB,&pin);
	
	// MISO Master Input Slave output
	pin.DIO_PinNumber = DIO_PIN_6;
	pin.DIO_Mood = DIO_Mood_Input_HIZ;
	MCAL_DIO_init(DIOB,&pin);
}

void SPI_Pins_Slave_init(void)
{
	DIO_PinConfig_t pin;
	
	// slave select
	pin.DIO_PinNumber = DIO_PIN_4;
	pin.DIO_Mood = DIO_Mood_Input_HIZ;
	MCAL_DIO_init(DIOB,&pin);
	
	// MOSI Master output Slave Input
	pin.DIO_PinNumber = DIO_PIN_5;
	pin.DIO_Mood = DIO_Mood_Input_HIZ;
	MCAL_DIO_init(DIOB,&pin);
	
	// SCK   clock
	pin.DIO_PinNumber = DIO_PIN_7;
	pin.DIO_Mood = DIO_Mood_Input_HIZ;
	MCAL_DIO_init(DIOB,&pin);
	
	// MISO Master Input Slave output
	pin.DIO_PinNumber = DIO_PIN_6;
	pin.DIO_Mood = DIO_Mood_Output;
	MCAL_DIO_init(DIOB,&pin);
	
}


/**================================================================
 * @Fn		  - MCAL_SPI_init
 * @brief 	  - initialization the configuration of SPI 
 * @param[in] - base address of SPI 
 * @param[in] - PinConfig pointer to SPI_PinConfig_t structure
 * @retval	  - none
 * Note		  - none
 * 			  
================================================================**/
void MCAL_SPI_init(SPI_PinConfig_t *pinCinfig)
{
	
	switch(pinCinfig->SPI_interrupt)
	{
		case SPI_Interrupt_Enable:
			SPI->SPCR_m |=SPIE_m;
			break;
		case SPI_Interrupt_Disable:
			SPI->SPCR_m &=~(SPIE_m);
			break;
	}
	if (pinCinfig->SPI_Direction == SPI_Dir_Master)
	{
		SPI->SPCR_m |= (MSTR_m);
		SPI_Pins_Master_init();
		switch(pinCinfig->SPI_Data_order)
		{
			case SPI_Data_order_LSB :
				SPI->SPCR_m |= (DORD_m);
				break;
			case SPI_Data_order_MSB :
				SPI->SPCR_m &= ~(DORD_m);
				break;
		}
		switch(pinCinfig->SPI_Mode)
		{
			case SPI_Mode_0:
				SPI->SPCR_m &= ~(CPOL_m);
				SPI->SPCR_m &= ~(CPHA_m);
				break;
			case SPI_Mode_1:
				SPI->SPCR_m &= ~(CPOL_m);
				SPI->SPCR_m |= (CPHA_m);
				break;
			case SPI_Mode_2:
				SPI->SPCR_m |= (CPOL_m);
				SPI->SPCR_m &= ~(CPHA_m);
				break;
			case SPI_Mode_3:
				SPI->SPCR_m |= (CPOL_m);
				SPI->SPCR_m |= (CPHA_m);
				break;
		}
		switch(pinCinfig->SPI_Clock_Rate)
		{
			case SPI_Clock_Rate_Fosc_D4:
				SPI->SPCR_m &= ~(SPR0_m);
				SPI->SPCR_m &= ~(SPR1_m);
				SPI->SPSR_m &= ~(SPR0_m);
				break;
			case SPI_Clock_Rate_Fosc_D16:
				SPI->SPCR_m |=  (SPR0_m);
				SPI->SPCR_m &= ~(SPR1_m);
				SPI->SPSR_m &= ~(SPR0_m);
				break;
			case SPI_Clock_Rate_Fosc_D64:
				SPI->SPCR_m &= ~(SPR0_m);
				SPI->SPCR_m |=  (SPR1_m);
				SPI->SPSR_m &= ~(SPR0_m);
				break;
			case SPI_Clock_Rate_Fosc_D128:
				SPI->SPCR_m |=  (SPR0_m);
				SPI->SPCR_m |=  (SPR1_m);
				SPI->SPSR_m &= ~(SPR0_m);
				break;	
			case SPI_Clock_Rate_D_Fosc_D4:
				SPI->SPCR_m &= ~(SPR0_m);
				SPI->SPCR_m &= ~(SPR1_m);
				SPI->SPSR_m |=  (SPR0_m);
				break;
			case SPI_Clock_Rate_D_Fosc_D16:
				SPI->SPCR_m |=  (SPR0_m);
				SPI->SPCR_m &= ~(SPR1_m);
				SPI->SPSR_m |=  (SPR0_m);
				break;
			case SPI_Clock_Rate_D_Fosc_D64:
				SPI->SPCR_m &= ~(SPR0_m);
				SPI->SPCR_m |=  (SPR1_m);
				SPI->SPSR_m |=  (SPR0_m);
				break;
			case SPI_Clock_Rate_D_Fosc_D128:
				SPI->SPCR_m |=  (SPR0_m);
				SPI->SPCR_m |=  (SPR1_m);
				SPI->SPSR_m |=  (SPR0_m);
				break;
		}
	}
	else if (pinCinfig->SPI_Direction == SPI_Dir_Slave)
	{
		SPI->SPCR_m &= ~(MSTR_m);
		SPI_Pins_Slave_init();
	}
	
	// Enable SPI 
	SPI->SPCR_m |= SPE_m;
}

/**================================================================
 * @Fn		  - MCAL_SPI_send_Byte
 * @brief 	  - Send data from master to slave 
 * @param[in] - the sending data
 * @param[in] - PinConfig pointer to SPI_PinConfig_t structure
 * @retval	  - none
 * Note		  - none
 * 			  
================================================================**/
void MCAL_SPI_send_Data(uint8_t Data)
{
	SPI->SPDR_m = Data;
	Wait_Transmition_complete();	
}

/**================================================================
 * @Fn		  - MCAL_SPI_Receive_Byte
 * @brief 	  - Receiving the data from the master
 * @param[in] - PinConfig pointer to SPI_PinConfig_t structure
 * @retval	  - the receiving data
 * Note		  - none
 * 			  
================================================================**/
uint8_t MCAL_SPI_Receive_Data()
{
	Wait_Transmition_complete();
	return SPI->SPDR_m;
}
/**================================================================
 * @Fn		  - MCAL_SPI_send_Receive_Byte
 * @brief 	  - Sending and Receiving the data 
 * @param[in] - PinConfig pointer to SPI_PinConfig_t structure
 * @param[in] - the sending data 
 * @retval	  - the receiving data
 * Note		  - none
 * 			  
================================================================**/
uint8_t MCAL_SPI_send_Receive_Data(uint8_t Data)
{
	SPI->SPDR_m = Data;
	Wait_Transmition_complete();
	return SPI->SPDR_m;
}
