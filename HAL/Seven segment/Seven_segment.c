/*
 * Seven_segment.c
 *
 * Created: 01/02/2023 11:46:04 ص
 *  Author: Abotaleb
 */ 
#include "Seven_segment.h"

uint8_t Seven_segment_numbers[16] = 
{
	/*
		* * A * *
		*       *
		F       B
		*       *
		* * G * *	
		*		*
		E		C	
		*		*
		* *	D * *
	*/
	0b00111111,  //0
	0b00000110,	 //1		 	
	0b01011011,  //2
	0b01111001,  //3
	0b01100110,  //4 
	0b01101101,  //5
	0b01111101,  //6
	0b00000111,  //7
	0b01111111,  //8
	0b01101111,  //9
	0b01110111,  //A
	0b01111111,  //B
	0b00111001,  //C
	0b00111111,  //D
	0b01111001,  //E
	0b01110001,  //F
};
void HAL_Seven_segment_Write_numbrer(Typdef_DIOx_t *DIOx,uint8_t number)
{
	DIOx->DDRx |= 0x7F;         // 0b0111 1111     make seven pins in DIOx output
	switch (number)
	{
		case 0:
			DIOx->PORTx |=Seven_segment_numbers[0];
			break;
		case 1:
			DIOx->PORTx |=Seven_segment_numbers[1];
			break;
		case 2:
			DIOx->PORTx |=Seven_segment_numbers[2];
			break;
		case 3:
			DIOx->PORTx |=Seven_segment_numbers[3];
			break;
		case 4:
			DIOx->PORTx |=Seven_segment_numbers[4];
			break;
		case 5:
			DIOx->PORTx |=Seven_segment_numbers[5];
			break;
		case 6:
			DIOx->PORTx |=Seven_segment_numbers[6];
			break;
		case 7:
			DIOx->PORTx |=Seven_segment_numbers[7];
			break;
		case 8:
			DIOx->PORTx |=Seven_segment_numbers[8];
			break;
		case 9:
			DIOx->PORTx |=Seven_segment_numbers[9];
			break;
		case 'A':
			DIOx->PORTx |=Seven_segment_numbers[10];
			break;
		case 'B':
			DIOx->PORTx |=Seven_segment_numbers[11];
			break;
		case 'C':
			DIOx->PORTx |=Seven_segment_numbers[12];
			break;
		case 'D':
			DIOx->PORTx |=Seven_segment_numbers[13];
			break;
		case 'E':
			DIOx->PORTx |=Seven_segment_numbers[14];
			break;
		case 'F':
			DIOx->PORTx |=Seven_segment_numbers[15];
			break;
		default:
			DIOx->PORTx |=Seven_segment_numbers[0];
			break;
	}
}
	
void HAL_Seven_segment_Write_Allnumbrer(Typdef_DIOx_t *DIOx)
{
	DIOx->DDRx |= 0x7F;         // 0b0111 1111     make seven pins in DIOx output
	DIOx->PORTx = 0x00;
	uint8_t counter;
	for (counter = 0;counter <=15;counter++)
	{
		DIOx->PORTx |= Seven_segment_numbers[counter];
		_delay_ms(5000);
		DIOx->PORTx &=(0b10000000);
	}
}