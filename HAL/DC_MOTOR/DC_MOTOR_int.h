/*
 * DC_MOTOR_init.h
 *
 *  Created on: Jul 1, 2024
 *      Author: user
 */

#ifndef HAL_DC_MOTOR_DC_MOTOR_INT_H_
#define HAL_DC_MOTOR_DC_MOTOR_INT_H_

ES_t DCMOTOR_enuInit(void);

ES_t DCMOTOR_enuChangeDirection(u8 Copy_u8Direction);

ES_t DCMOTOR_enuSpeed(u8 Copy_u8Speed);

ES_t DCMOTOR_enuStop();


#endif /* HAL_DC_MOTOR_DC_MOTOR_INT_H_ */
