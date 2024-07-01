/*
 * Thermistor_prog.c
 *
 *  Created on: Feb 21, 2024
 *      Author: samar ibrahim
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/ADC/ADC_Config.h"
#include "../../MCAL/ADC/ADC_int.h"


#include "Thermistor_config.h"

#include "Thermistor_priv.h"


static volatile u16 ADCValue = 0;
static volatile f32 LM35_f32Tempeture = 0;

void LM35_inlvidReadADCValue(void *Copy_PvidLM35VOLT);

ES_t Thermistor_enuInit(Themistor_t* Copy_PstrLM35config){
	ES_t Local_enuErrorState = ES_NOK;
	ADC_enuInit();
	ADC_enuEnableInterruptrMode();
    ADC_enuCallBack(LM35_inlvidReadADCValue,&ADCValue);
GIE_enuGloable_Interrupt_Enable();

u8 Local_u8Iterrator = 0;
	for(Local_u8Iterrator = 0; Local_u8Iterrator < LM35NUM; Local_u8Iterrator++)
	{
		if(Copy_PstrLM35config[Local_u8Iterrator].LM35_postiveChannel != NOTCONNECTED)
		{
			DIO_enuSetPinDirection(DIO_u8PORTA, Copy_PstrLM35config[Local_u8Iterrator].LM35_postiveChannel, DIO_u8INPUT);
			ADC_enuSelectChannel(Copy_PstrLM35config[Local_u8Iterrator].LM35_postiveChannel);
		}

		if(Copy_PstrLM35config[Local_u8Iterrator].LM35_negativeChannel != NOTCONNECTED)
		{
			DIO_enuSetPinDirection(DIO_u8PORTA, Copy_PstrLM35config[Local_u8Iterrator].LM35_negativeChannel, DIO_u8INPUT);
			ADC_enuSelectChannel(Copy_PstrLM35config[Local_u8Iterrator].LM35_negativeChannel);
		}
	}

	ADC_enuEnable();
	return Local_enuErrorState;
}

void LM35_inlvidReadADCValue(void *Copy_PvidLM35VOLT){
	if(Copy_PvidLM35VOLT!=NULL){
		ADC_enuReadValue(Copy_PvidLM35VOLT);
	}

}
ES_t Themistor_enuGetTemp(u8 Copy_u8_LM35_ID,u8 *Copy_u8Temp){
	ES_t Local_enuErrorState = ES_NOK;

		if(Copy_u8Temp != NULL)
		{
			Local_enuErrorState = ADC_enuStartConversion();
			*Copy_u8Temp = (u8)(((u32)ADCValue *150*5 )/ (1023*1.5));
		}
		else
		{
			Local_enuErrorState = ES_NULL_POINTER;
		}

		return Local_enuErrorState;

}
