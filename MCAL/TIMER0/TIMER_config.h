/*
 * TIMER_config.h
 *
 *  Created on: Feb 29, 2024
 *      Author: samar ibrahim
 */

#ifndef MCAL_TIMER0_TIMER_CONFIG_H_
#define MCAL_TIMER0_TIMER_CONFIG_H_


#define TIMER_PRES    PRES_1024 /*choose from
NO_CLOCK_ SOURCE
PRES_NO
PRES_8
PRES_64
PRES_256
PRES_1024
FALLING_EDGE
RISING_EDGE     */

#define TIMER_MODE   OVF
#define OC_MODE      DISCONNECTED  /*pin output oc0 choose from
 DISCONNECTED
 TOGGLE
 CLEAR
 SET
 NON_INVERTED    use in pwm
 INVERTED        use in pwm
            */

#define TIMER_F_CPU  (1000UL)   // Write freq at KHz (1000UL mean 1MHz)
#endif /* MCAL_TIMER0_TIMER_CONFIG_H_ */
