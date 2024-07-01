/*
 * USART_config.h
 *
 *  Created on: Apr 26, 2024
 *      Author: samar ibrahim
 */

#ifndef MCAL_USART_USART_CONFIG_H_
#define MCAL_USART_USART_CONFIG_H_

/*NORMAL,DOUBLE*/
#define SPEED_MODE                      DOUBLE

/*TRANSMITTER,RECIEVER,TRANSCIEVER*/
#define UART_MODE                       TRANSCIEVER

#define BAUD_RATE                       9600UL

/*DATA_SIZE_5_BIT,DATA_SIZE_6_BIT,DATA_SIZE_7_BIT,DATA_SIZE_8_BIT,DATA_SIZE_9_BIT	*/
#define DATA_LENGTH                         DATA_SIZE_8_BIT

/* NO_PARITY,EVEN_PARITY,ODD_PARITY*/
#define PARITY_STATE                        NO_PARITY
/*ONE_STOP_BIT,TWO_STOP_BIT*/
#define STOP_STATE                          ONE_STOP_BIT

/* CLOCK MODE  ASYNCHRONOUS		 , SYNCHRONOUS */
#define CLOCK_MODE                          ASYNCHRONOUS


#endif /* MCAL_USART_USART_CONFIG_H_ */
