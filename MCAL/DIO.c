/*
 * DIO.c
 *
 * Created: 03/12/2022 12:27:17 م
 *  Author: Abotaleb
 */ 

#include "Includes/DIO.h"


/**================================================================
 * @Fn		  - MCAL_DIO_init
 * @brief 	  - initialization DIOx piny according to the specified parameters in pin configuration
 * @param[in] - base address of DIOx : can be (A ..... D )
 * @param[in] - PinConfig pointer to GPIO_PinConfig_t structure that contains
 * 			   the configuration information for specified GPIO pin
 * @retval	  - none
 * Note		  - none
 * 			  
================================================================**/
void MCAL_DIO_init(Typdef_DIOx_t *DIOx,DIO_PinConfig_t *DIO_config)
{
// DDxn      PORTxn        PUD(in SFIOR)          I/O            Pull-up       Comment
// 0         0             X                      Input          No            Tri-state (Hi-Z)
// 0         1             0                      Input          Yes           Pxn will source current if ext. pulled low.
// 0         1             1                      Input          No            Tri-state (Hi-Z)
// 1         0             X                      Output         No            Output Low (Sink)
// 1         1             X                      Output         No            Output High (Source)
	switch(DIO_config->DIO_Mood)
	{
		case DIO_Mood_Input_HIZ	:
			DIOx->DDRx  &= ~(DIO_config->DIO_PinNumber);
			DIOx->PORTx &= ~(DIO_config->DIO_PinNumber);
			break;
		case DIO_Mood_Input_PU	:
			DIOx->DDRx  &= ~(DIO_config->DIO_PinNumber);
			DIOx->PORTx |=  (DIO_config->DIO_PinNumber);
			break;
		case DIO_Mood_Output    :
			DIOx->DDRx  |=  (DIO_config->DIO_PinNumber);
			break;
	}
}
/**================================================================
 * @Fn        - MCAL_DIO_init_PORT
 * @brief     - initialization DIOx according to the specified parameters in pin configuration
 * @param[in] - base address of DIOx : can be (A ..... D )
 * @param[in] - PinConfig pointer to GPIO_PinConfig_t structure that contains
 *             the configuration information for specified GPIO pin
 * @retval    - none
 * Note       - none
 *            
================================================================**/
void MCAL_DIO_init_PORT(Typdef_DIOx_t *DIOx,DIO_PinConfig_t *DIO_config)
{
    switch(DIO_config->DIO_Mood)
    {
        case DIO_Mood_Input_HIZ :
            DIOx->DDRx  = 0x00;
            DIOx->PORTx = 0x00;
            break;
        case DIO_Mood_Input_PU  :
            DIOx->DDRx  = 0x00;
            DIOx->PORTx = 0xFF;
            break;
        case DIO_Mood_Output    :
            DIOx->DDRx  = 0xFF;
            break;
    }

}

/**================================================================
 * @Fn		  - MCAL_DIO_Deinit
 * @brief 	  - Reset all DIOx pins
 * @param[in] - base address of GPIOx : can be (A ..... D )
 * @retval	  - none
 * Note		  - none
================================================================**/

void MCAL_DIO_Deinit(Typdef_DIOx_t *DIOx)
{
	DIOx->DDRx=0x00;
	DIOx->PORTx =0x00;
}


/**================================================================
 * @Fn		  - MCAL_DIO_Write_pin
 * @brief 	  - write specified pin on DIOx :can be (A ..... D )
 * @param[in] - base address of DIOx :can be (A ..... D )
 * @param[in] - pin number set by @ref DIO_PINS_define
 * @param[in] - pin value
 * @retval	  - none
 * Note		  - none
================================================================**/

void MCAL_DIO_Write_pin(Typdef_DIOx_t *DIOx,uint8_t Pin_number,uint8_t value)
{
	if(value == DIO_PIN_High)			DIOx->PORTx |=Pin_number;		
	else if(value == DIO_PIN_Low)	    DIOx->PORTx &=~Pin_number;	
}
/**================================================================
 * @Fn		  - MCAL_DIO_Write_Port
 * @brief 	  - write specified GPIOx :can be (A ..... D )
 * @param[in] - base address of GPIOx :can be (A ..... D )
 * @param[in] - port value
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_DIO_Write_Port(Typdef_DIOx_t *DIOx,uint8_t value)
{
	DIOx->DDRx=0xFF;
	DIOx->PORTx =value;
}

/**================================================================
 * @Fn		  - MCAL_DIO_Read_Pin
 * @brief 	  - Read specified pin
 * @param[in] - base address of DIOx : can be (A ..... D )
 * @param[in] - pin number set by @ref DIO_PINS_define
 * @retval	  - the input pin value according to @ref DIO_PIN_state
 * Note		  - none
================================================================**/
uint8_t MCAL_DIO_Read_Pin(Typdef_DIOx_t *DIOx,uint8_t Pin_number)
{
	uint8_t Pin;
	if (( (DIOx->PINx) & Pin_number)!=(uint8_t)DIO_PIN_Low)
	{
		Pin = 1;
	}
	else
	{
		Pin =0;
	}
	return Pin;
}

/**================================================================
 * @Fn		  - MCAL_DIO_Read_Port
 * @brief 	  - Read specified port
 * @param[in] - base address of DIOx : can be (A ..... D )
 * @retval	  - the input port value
 * Note		  - none
================================================================**/
uint8_t MCAL_DIO_Read_Port(Typdef_DIOx_t *DIOx)
{
	uint8_t PORT_value;
	PORT_value=DIOx->PINx;
	return PORT_value;
}

/**================================================================
 * @Fn		  - MCAL_DIO_Toggle_Pin
 * @brief 	  - toggle specified GPIOx piny
 * @param[in] - base address of DIOx :can be (A ..... D )
 * @param[in] - pin number set by @ref DIO_PINS_define
 * @retval	  - none
 * Note		  - none
================================================================**/

void MCAL_DIO_Toggle_Pin(Typdef_DIOx_t *DIOx,uint8_t Pin_number)
{
	DIOx->PORTx ^=Pin_number;
}

/**================================================================
 * @Fn		  - MCAL_DIO_Toggle_Port
 * @brief 	  - toggle specified DIOx 
 * @param[in] - base address of DIOx :can be (A ..... D )
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_DIO_Toggle_Port(Typdef_DIOx_t *DIOx)
{
	DIOx->DDRx = 0xFF;
	MCAL_DIO_Toggle_Pin(DIOx,DIO_PIN_0);
	MCAL_DIO_Toggle_Pin(DIOx,DIO_PIN_1);     
 	MCAL_DIO_Toggle_Pin(DIOx,DIO_PIN_2);
 	MCAL_DIO_Toggle_Pin(DIOx,DIO_PIN_3);
 	MCAL_DIO_Toggle_Pin(DIOx,DIO_PIN_4);
 	MCAL_DIO_Toggle_Pin(DIOx,DIO_PIN_5);
 	MCAL_DIO_Toggle_Pin(DIOx,DIO_PIN_6);
 	MCAL_DIO_Toggle_Pin(DIOx,DIO_PIN_7);
}