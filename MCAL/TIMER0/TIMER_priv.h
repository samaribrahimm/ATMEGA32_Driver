/*
 * TIMER_priv.h
 *
 *  Created on: Feb 29, 2024
 *      Author: samar ibrahim
 */

#ifndef MCAL_TIMER0_TIMER_PRIV_H_
#define MCAL_TIMER0_TIMER_PRIV_H_

/*timer mode */
#define OVF                 1
#define CTC                 2
#define FASTPWM             3
#define PWM_PHASECORRECT     4


/*OC0 Mode*/
#define DISCONNECTED            12
#define TOGGLE       			1
#define CLEAR				    2
#define SET					    3
#define NON_INVERTED			4
#define INVERTED				5

/*bits in TCCR0 – Timer/Counter Control Register */
#define CS00    0
#define CS01    1
#define CS02    2
#define WGM01   3
#define COM00   4
#define COM01   5
#define WGM00   6
#define FOC0    7
/*bits in TIMSK – Timer/Counter Interrupt Mask Register*/
#define OCIE0  1
#define TOIE0  0
/*bits in TIFR – Timer/Counter Interrupt Flag Register*/
#define OCF0   1
#define TOV0   0

 /*prescaler*/
#define  NO_CLOCK_ SOURCE   0             //(Timer/Counter stopped).
#define  PRES_NO            1            //(No prescaling)
#define  PRES_8             8           //(From prescaler)
#define  PRES_64            64         // (From prescaler)
#define  PRES_256           256       // (From prescaler)
#define  PRES_1024          1024     //(From prescaler)
#define  FALLING_EDGE       12       //External clock source on T0 pin. Clock on
#define  RISING_EDGE        13      // External clock source on T0 pin. Clock on

/*
 * TIMER REGISTERS
 */

/*TIMSK*/
#define TIMSK	*((volatile u8*) 0x59)

/*TIFR*/
#define TIFR	*((volatile u8*) 0x58)

/*TCCR*/
#define TCCR0	*((volatile u8*) 0x53)
#define TCCR1A	*((volatile u8*) 0x4f)
#define TCCR1B	*((volatile u8*) 0x4e)
#define TCCR2	*((volatile u8*) 0x45)

/*TCNT*/
#define TCNT0	*((volatile u8*) 0x52)

#define TCNT1H	*((volatile u8*) 0x4d)
#define TCNT1L	*((volatile u8*) 0x4c)

#define TCNT1	*((volatile u16*) 0x4c)

#define TCNT2	*((volatile u8*) 0x44)

/*OCR*/
#define OCR0	*((volatile u8*) 0x5c)
#define OCR1AH	*((volatile u8*) 0x4b)
#define OCR1AL	*((volatile u8*) 0x4a)

#define OCR1A	*((volatile u16*) 0x4a)

#define OCR1BH	*((volatile u8*) 0x49)
#define OCR1BL	*((volatile u8*) 0x48)

#define OCR1B	*((volatile u16*) 0x48)

#define OCR2	*((volatile u8*) 0x43)


#endif /* MCAL_TIMER0_TIMER_PRIV_H_ */
