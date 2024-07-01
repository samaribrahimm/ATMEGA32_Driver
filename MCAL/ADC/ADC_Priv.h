/*
 * ADC_Priv.h
 *
 *  Created on: Feb 17, 2024
 *      Author: samar ibrahim
 */

#ifndef MCAL_ADC_ADC_PRIV_H_
#define MCAL_ADC_ADC_PRIV_H_
 /*VREF*/
#define AVREF           1
#define AVCC           5000UL
#define INTERNAL_VREF   2560UL

/*adjustment*/
#define RIGHT_ADJUST    4
#define LEFT_ADJUST     5

/*Prescaler */
#define DIVISION_FACTOR_2			1
#define DIVISION_FACTOR_4			2
#define DIVISION_FACTOR_8			3
#define DIVISION_FACTOR_16			4
#define DIVISION_FACTOR_32			5
#define DIVISION_FACTOR_64			6
#define DIVISION_FACTOR_128			7


 /* ADC register */
#define ADMUX  *((volatile u8 *)0x27)
#define ADCSRA *((volatile u8 *)0x26)
#define ADCH   *((volatile u8 *)0x25)
#define ADCL   *((volatile u8 *)0x24)
#define SFIOR  *((volatile u8 *)0x50)

/*MASK BIT*/
#define MASK_BIT 1

/*BITS IN REGISTER*/
#define BIT0  0
#define BIT1  1
#define BIT2  2
#define BIT3  3
#define BIT4  4
#define BIT5  5
#define BIT6  6
#define BIT7  7

// TriggerMode
#define FREE_RUNNING_MODE			    1
#define ANALOG_COMPARATOR			    2
#define EXTI0_TRIG					    3
#define TIMER0_COMPARE_MATCH_TRIG	    4
#define TIMER0_OVERFLOW_TRIG		    5
#define TIMER1_COMPARE_MATCH_TRIG	    6
#define TIMER1_OVERFLOW_TRIG		    7
#define TIMER1_CAPUTRE_TRIG			    8
#endif /* MCAL_ADC_ADC_PRIV_H_ */
