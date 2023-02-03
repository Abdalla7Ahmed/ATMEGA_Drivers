/*
 * Kaypad.c
 *
 * Created: 14/09/2022 07:35:38 AM
 *  Author: Abotaleb
 */ 

#include "Kaypad.h"

uint32_t Kaypad_column[]={C0,C1,C2,C3};
uint32_t Kaypad_Row[]={R0,R1,R2,R3};

void KAYPAD_INIT()
{
	// set rows as an input
	CLEARBIT(Data_Dir_KAYPAD_PORT,R0);
	CLEARBIT(Data_Dir_KAYPAD_PORT,R1);
	CLEARBIT(Data_Dir_KAYPAD_PORT,R2);
	CLEARBIT(Data_Dir_KAYPAD_PORT,R3);
	
		// set column as an output
	SETBIT(Data_Dir_KAYPAD_PORT,C0);
	SETBIT(Data_Dir_KAYPAD_PORT,C1);
	SETBIT(Data_Dir_KAYPAD_PORT,C2);
	SETBIT(Data_Dir_KAYPAD_PORT,C3);

	
	KAYPAD_PORT =0xFF;



}
char GET_CHARACTER()
{
	uint32_t i,j;
	for (i=0;i<4;i++)
	{
		SETBIT(KAYPAD_PORT,Kaypad_column[0]);
		SETBIT(KAYPAD_PORT,Kaypad_column[1]);
		SETBIT(KAYPAD_PORT,Kaypad_column[2]);
		SETBIT(KAYPAD_PORT,Kaypad_column[3]);
		CLEARBIT(KAYPAD_PORT,Kaypad_column[i]);
		for (j=0;j<4;j++)
		{
			if (READBIT(KAYPAD_PIN,Kaypad_Row[j])==0)
			{
				while (READBIT(KAYPAD_PIN,Kaypad_Row[j])==0);
				switch(i)
				{
					case 0:
					{
						if (j==0)     return '7';
						else if (j==1)return '4';
						else if (j==2)return '1';
						else if (j==3)return 'C';
						break;
					}
					case 1:
					{
						if (j==0)     return '8';
						else if (j==1)return '5';
						else if (j==2)return '2';
						else if (j==3)return '0';
						break;
					}
					case 2:
					{
						if (j==0)     return '9';
						else if (j==1)return '6';
						else if (j==2)return '3';
						else if (j==3)return '=';
						break;
					}
					case 3:
					{
						if (j==0)     return '/';
						else if (j==1)return '*';
						else if (j==2)return '-';
						else if (j==3)return '+';
						break;
					}
				}
			}
		}
		
	}
	return 'N'; // return null 
}
