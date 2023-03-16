/*
 * Ultrasonic_Sensor.c
 *
 * Created: 16/02/2023 05:35:15 م
 *  Author: Abotaleb
 */ 

#include "Includes/Ultrasonic_Sensor.h"
DIO_PinConfig_t Trigger_Pin;
Timer1_config_t Timer1;

static uint8_t Flag = 0;
static uint16_t T1 =0;
static uint16_t T2 = 0;
static uint16_t Counter =0; 
static uint32_t Time = 0;

void Input_Capture_IRQ_Callback(void);
void Over_Floww_IRQ_Callback(void);



void Ultrasonic_Init(void)
{

	/* ================ Timer1 Configuration  =============== */
	Timer1.Clock_Select = prescaling_8 ;
	Timer1.OC1_state = OC1A_OC1B_Disconnected ;
	Timer1.Waveform_Generation = Normal_TOP_0xFFFF;
	Timer1.Timer1_Interrupt = (Interrupt_Input_Capture | Interrupt_Enable_Overflow);
	Timer1.Input_Capture_Edge_Select= Input_Capture_Edge_Select_Rising;
	Timer1.P_Overflow_IRQ_Callback = Over_Floww_IRQ_Callback;
	Timer1.P_Input_Capture_IRQ_Callback = Input_Capture_IRQ_Callback;
	MCAL_Timer1_init(&Timer1);
}

void HAL_Ultrasonic_Start(uint8_t DIO_Number)
{
 	Timer1_Enable_Input_Capture_Interrupt();
	Timer1_Enable_OverFlow_Interrupt();
	_TCCR1B |=(Input_Capture_Edge_Select_Rising );

	/* ================ Ultrasonic Pin Trigger configuration =============== */
	Trigger_Pin.DIO_PinNumber = DIO_Number;
	Trigger_Pin.DIO_Mood = DIO_Mood_Output;
	MCAL_DIO_init(Ultasonic_PORT,&Trigger_Pin);
	
	/* ================ Strat Ultrasonic  =============== */
	MCAL_DIO_Write_pin(Ultasonic_PORT,DIO_Number,DIO_PIN_High);
	_delay_us(20);
	MCAL_DIO_Write_pin(Ultasonic_PORT,DIO_Number,DIO_PIN_Low);
	

}
uint8_t HAL_Ultrasonic_Get_Distansc(uint8_t *Distance)
{
	
	if (Flag == 2)
	{
		Time = (uint16_t)(T2  + ((uint32_t)(Counter * 65535)) - T1)  ;
		*Distance = (uint8_t)( (Time / 58 ) +1 ); // ((Time /2) * 340  * 100) / 1000000
		Flag = 0;
		return 1;
	}
	return 0;
	
}


void Over_Floww_IRQ_Callback(void)
{
	Counter ++;
}

void Input_Capture_IRQ_Callback(void)
{

	if (Flag == 0)
	{
		 MCAL_Timer1_GET_TCNT1_Value(&T1);
		 _TCCR1B &= ~ (Input_Capture_Edge_Select_Rising );
		Flag = 1;
	}
	else if (Flag == 1)
	{
		MCAL_Timer1_GET_TCNT1_Value(&T2);
		Timer1_Disable_Input_Capture_Interrupt();
		Timer1_Disable_OverFlow_Interrupt();
		Flag = 2;
	}
}