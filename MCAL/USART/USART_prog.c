/*
 * USART_prog.c
 *
 *  Created on: Apr 26, 2024
 *      Author: samar ibrahim
 */
#include"../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "USART_priv.h"
#include "USART_config.h"

ES_t UART_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if SPEED_MODE == NORMAL
	UCSRA &= ~ (1<<U2X);
	Local_enuErrorState = ES_OK;
#elif SPEED_MODE == DOUBLE
	UCSRA |= (1<<U2X);
	Local_enuErrorState = ES_OK;
#else
#error "WRONG SPEED MODE"
#endif

#if UART_MODE == TRANSMITTER
	UCSRB |= (1<<TXEN);
	Local_enuErrorState = ES_OK;
#elif UART_MODE == RECIEVER
	UCSRB |= (1<<RXEN);
	Local_enuErrorState = ES_OK;
#elif UART_MODE == TRANSCIEVER
	UCSRB |= (1<<TXEN);
	UCSRB |= (1<<RXEN);
	Local_enuErrorState = ES_OK;
#else
#error "WRONG UART MAODE"
#endif

	u8 Local_u8UCSRC=0;
#if DATA_LENGTH == DATA_SIZE_5_BIT

	Local_u8UCSRC &= ~ (1<<UCSZ0);
	Local_u8UCSRC &= ~ (1<<UCSZ1);
	Local_enuErrorState = ES_OK;
#elif DATA_LENGTH == DATA_SIZE_6_BIT
	Local_u8UCSRC |= (1<<UCSZ0);
	Local_u8UCSRC &= ~ (1<<UCSZ1);
	Local_enuErrorState = ES_OK;
#elif DATA_LENGTH == DATA_SIZE_7_BIT
	Local_u8UCSRC &= ~ (1<<UCSZ0);
	Local_u8UCSRC |= (1<<UCSZ1);
	Local_enuErrorState = ES_OK;
#elif DATA_LENGTH == DATA_SIZE_8_BIT
	Local_u8UCSRC |= (1<<UCSZ0);
	Local_u8UCSRC |= (1<<UCSZ1);
	Local_enuErrorState = ES_OK;
#elif DATA_LENGTH == DATA_SIZE_9_BIT
	Local_u8UCSRC |= (1<<UCSZ0)
	Local_u8UCSRC |= (1<<UCSZ1)
	UCSRB |= (1<<UCSZ2);
	Local_enuErrorState = ES_OK;
#else
#error "WRONG DATA LENGTH"
#endif

#if PARITY_STATE == NO_PARITY
	Local_u8UCSRC &= ~ (1<<UPM0);
	Local_u8UCSRC &= ~ (1<<UPM1);
	Local_enuErrorState = ES_OK;
#elif PARITY_STATE == EVEN_PARITY
	Local_u8UCSRC &= ~ (1<<UPM0);
	Local_u8UCSRC |= (1<<UPM1);
	Local_enuErrorState = ES_OK;
#elif PARITY_STATE == ODD_PARITY
	Local_u8UCSRC |= (1<<UPM0);
	Local_u8UCSRC |= (1<<UPM1);
	Local_enuErrorState = ES_OK;
#else
#error "WRONG PARITY"
#endif

#if STOP_STATE == ONE_STOP_BIT
	Local_u8UCSRC &= ~ (1<<USBS);
	Local_enuErrorState = ES_OK;
#elif STOP_STATE == TWO_STOP_BIT
	Local_u8UCSRC |= (1<<USBS);
	Local_enuErrorState = ES_OK;
#else
#error "WRONG STOP STATE"
#endif

#if CLOCK_MODE == ASYCH
	Local_u8UCSRC &= ~ (1<<UMSEL);
	Local_enuErrorState = ES_OK;
#elif CLOCK_MODE==SYCH
	Local_u8UCSRC |= (1<<UMSEL);
	Local_enuErrorState = ES_OK;
#else
#error "WRONG CLOCK MODE"
#endif

	Local_u8UCSRC |= (1<<URSEL);//to select UCSRC

	UCSRC = Local_u8UCSRC;

	u16 Local_u16UBRR = BAUDEQN(BAUD_RATE);

	UBRRL = (u8)Local_u16UBRR;
	UBRRH |= (Local_u16UBRR>>8);

	return Local_enuErrorState;
}

ES_t UART_enuSendChar(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_NOK;

	while( ! ( ( UCSRA >> UDRE ) & 1 ) );
	UDR = Copy_u8Data;

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t UART_enuRecieveChar(u8 *Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

	if( Copy_u8Data != NULL )
	{
	   while( ! ( ( UCSRA >> RXC ) & 1 ) );
	   *Copy_u8Data = UDR;
	   Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t UART_enuSendString(const char* Copy_sData)
{
	ES_t Local_enuErrorState = ES_NOK;

	while(*Copy_sData != '\0')
	{
		while( ! ( ( UCSRA >> UDRE ) & 1 ) );
		UDR = *Copy_sData;
		Copy_sData++;
	}

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t UART_enuRecieveString(char* Copy_sData)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8Data = 0,Local_u8Index = 0;
	while(1)
	{
		   while( ! ( ( UCSRA >> RXC ) & 1 ) );
		   Local_u8Data = UDR;
		   if(Local_u8Data == '\r' || Local_u8Data == '\n')//enter
		   {
			   Copy_sData[Local_u8Index] = '\0';
			   break;
		   }
		   else
		   {
			   Copy_sData[Local_u8Index] = Local_u8Data;
			   Local_u8Index++;
		   }
	}
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}
