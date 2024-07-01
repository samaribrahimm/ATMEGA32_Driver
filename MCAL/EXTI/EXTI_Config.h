/*
 * EXTI_Config.h
 *
 *  Created on: Feb 5, 2024
 *      Author: samar ibrahim
 */

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

typedef struct {
	u8 EXTI_u8State;
	u8 EXTI_u8SenseLevel;
}EXTI_t;


#define INT0 0
#define INT1 1
#define INT2 2

#endif /* EXTI_CONFIG_H_ */
