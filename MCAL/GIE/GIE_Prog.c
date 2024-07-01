/*
 * GIE_Prog.c
 *
 *  Created on: Feb 7, 2024
 *      Author: samar ibrahim
 */


#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "GIE_priv.h"

ES_t GIE_enuGloable_Interrupt_Enable(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	SREG &= ~(1 << GIE_I);
	SREG |= (1 << GIE_I);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t GIE_enuGloable_Interrupt_Disable(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	SREG &= ~(1<< GIE_I);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}
