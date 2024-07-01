/*
 * LED_config.c
 *
 *  Created on: Oct 27, 2023
 *      Author: samar ibrahim
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "LED_priv.h"
#include "LED_config.h"
#include "LED_int.h"

#include "../../MCAL/DIO/DIO_int.h"
LED_t LED_AstrLedConfig[LED_NUM]={
	{DIO_u8PORTA,DIO_u8PIN0,LED_SINK,LED_OFF},
	{DIO_u8PORTA,DIO_u8PIN0,LED_SINK,LED_ON},
	{DIO_u8PORTB,DIO_u8PIN0,LED_SOURCE,LED_OFF}
};

