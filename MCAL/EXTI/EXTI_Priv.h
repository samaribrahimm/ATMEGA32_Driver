/*
 * EXTI_Priv.h
 *
 *  Created on: Feb 5, 2024
 *      Author: samar ibrahim
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_

// States of INT
#define ENABLE		    1
#define DISABLE 		2

// Sense levels
#define RISING_EDGE			1
#define FALLING_EDGE		2
#define ANY_LOGIC			3
#define LOW_LEVEL			4

// registers
#define MCUCR				*((u8*)0x55)
#define MCUCSR				*((u8*)0x54)
#define GICR				*((u8*)0x5B)
#define GIFR				*((u8*)0x5A)

// INT
#define INT0   0
#define INT1   1
#define INT2   2

#endif /* EXTI_PRIV_H_ */
