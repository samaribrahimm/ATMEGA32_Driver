/*
 * USART_priv.h
 *
 *  Created on: Apr 26, 2024
 *      Author:samar ibrahim
 */

#ifndef MCAL_USART_USART_PRIV_H_
#define MCAL_USART_USART_PRIV_H_

/* Register of USART */
#define UDR * ((volatile u8 *) 0X2C)

#define UCSRA           * ((volatile u8 *) 0X2B)
#define RXC		7
#define TXC		6
#define UDRE		5
#define FE		4
#define DOR		3
#define PE		2
#define U2X		1
#define MPCM		0

#define UCSRB           * ((volatile u8 *) 0X2A)
#define RXCIE		7
#define TXCIE		6
#define UDRIE		5
#define RXEN		4
#define TXEN		3
#define UCSZ2		2
#define RXB8		1
#define TXB8		0

#define UCSRC           * ((volatile u8 *) 0X40)
#define URSEL 	7
#define UMSEL		6
#define UPM1		5
#define UPM0		4
#define USBS		3
#define UCSZ1		2
#define UCSZ0		1
#define UCPOL		0

#define UBRRL           * ((volatile u8 *) 0X29)

#define UBRRH           * ((volatile u8 *) 0X40)
#define UBRRH_URSEL		7

/*********************************************************/

//#define DISABLE				                    0
//#define ENABLE				                    1

/*speed normal or double*/
#define NORMAL                            2
#define DOUBLE                            1




#define ONE_STOP_BIT 		                    0
#define TWO_STOP_BIT 			                    1

/* Data Length*/
#define DATA_SIZE_5_BIT		                    0
#define DATA_SIZE_6_BIT		                    1
#define DATA_SIZE_7_BIT		                    2
#define DATA_SIZE_8_BIT		                    3
#define DATA_SIZE_9_BIT		                    4

/*UART Modes*/
#define TRANSMITTER                       0
#define RECIEVER                          1
#define TRANSCIEVER                       2

/*Parity*/
#define NO_PARITY                         0
#define EVEN_PARITY                       1
#define ODD_PARITY                        2

/*Clock*/
#define ASYNCHRONOUS		                    0
#define SYNCHRONOUS 		                    1


//equation for baud rate
#define BAUDEQN(BAUD_RATE)                (u16)((F_CPU/(SPEED_MODE*8*BAUD_RATE))-1)

#define XCK_RISING_TX_XCH_FALLING_RX			0
#define XCK_RISING_RX_XCH_FALLING_TX			1

#define UBRRL_MAX								256




#endif /* MCAL_USART_USART_PRIV_H_ */








