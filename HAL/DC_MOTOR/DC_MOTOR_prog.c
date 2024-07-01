/*
 * DC_MOTOR_prog.c
 *
 *  Created on: Jul 1, 2024
 *      Author: user
 */


#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/DIO/DIO_config.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "../../MCAL/TIMER0/TIMER_config.h"
#include "../../MCAL/TIMER0/TIMER_int.h"

#include "DC_MOTOR_priv.h"
#include "DC_MOTOR_config.h"


ES_t DCMOTOR_enuInit(void)
{
	ES_t Local_enuErrorStates=ES_NOK;

	Local_enuErrorStates = DIO_enuSetPinDirection(DC_IN1_PORT,DC_IN1_PIN,DIO_u8OUTPUT);
	Local_enuErrorStates = DIO_enuSetPinDirection(DC_IN2_PORT,DC_IN2_PIN,DIO_u8OUTPUT);

	Local_enuErrorStates = DIO_enuSetPinVal(DC_IN1_PORT,DC_IN1_PIN,DIO_u8LOW);
	Local_enuErrorStates = DIO_enuSetPinVal(DC_IN2_PORT,DC_IN2_PIN,DIO_u8LOW);

	Local_enuErrorStates = DIO_enuSetPinDirection(DIO_u8PORTB,DIO_u8PIN3,DIO_u8OUTPUT);//OC pin
	Local_enuErrorStates = TIMER0_enuInit();

	return Local_enuErrorStates;
}

ES_t DCMOTOR_enuChangeDirection(u8 Copy_u8Direction)
{
	ES_t Local_enuErrorStates=ES_NOK;

#if Copy_u8Direction == ROTATE_CLKWISE
	Local_enuErrorStates = DIO_enuSetPinVal(DC_IN1_PORT,DC_IN1_PIN,DIO_u8LOW);
	Local_enuErrorStates = DIO_enuSetPinVal(DC_IN2_PORT,DC_IN2_PIN,DIO_u8HIGH);
#elif Copy_u8Direction == ROTATE_ANTI_CLKWISE
	Local_enuErrorStates = DIO_enuSetPinVal(DC_IN1_PORT,DC_IN1_PIN,DIO_u8HIGH);
	Local_enuErrorStates = DIO_enuSetPinVal(DC_IN2_PORT,DC_IN2_PIN,DIO_u8LOW);
#else
#error "WRONG DIRECTION";
#endif

	return Local_enuErrorStates;
}

ES_t DCMOTOR_enuSpeed(u8 Copy_u8Speed)
{
	ES_t Local_enuErrorStates=ES_NOK;

	Local_enuErrorStates = TIMER0_enuGeneratePWM(Copy_u8Speed);

	return Local_enuErrorStates;
}

ES_t DCMOTOR_enuStop()
{
	ES_t Local_enuErrorStates=ES_NOK;

	Local_enuErrorStates = DIO_enuSetPinVal(DC_IN1_PORT,DC_IN1_PIN,DIO_u8LOW);
	Local_enuErrorStates = DIO_enuSetPinVal(DC_IN2_PORT,DC_IN2_PIN,DIO_u8LOW);

	return Local_enuErrorStates;
}
