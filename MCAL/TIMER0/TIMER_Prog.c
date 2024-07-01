/*
 * TIMER_Prog.c
 *
 *  Created on: Feb 29, 2024
 *      Author: samar ibrahim
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../interrupt.h"

#include "../TIMER0/TIMER_config.h"
#include "../TIMER0/TIMER_priv.h"



 volatile static void (*Timer0_ApFun_OVF)(void*) = NULL;
volatile static void * Timer0_Apvidparameter_OVF= NULL;

volatile static void (*TIMER0_PFun_CTC)(void *) = NULL;
volatile static void *TIMER0_Pvidparameter_CTC = NULL;

u32 Global_u32NumOvf=0;
u8 Global_u8Preload=0;
u32 TIMER0_f32OC0Val=0;
ES_t TIMER0_enuInit(void){
	ES_t Local_enuErrorState = ES_NOK;
	TCCR0&=0xB7; //mask bit for modes

#if  TIMER_MODE==OVF
	TCCR0 &= ~(1 << WGM00);
	TCCR0 &= ~(1 << WGM01);

#elif TIMER_MODE==CTC
	 TCCR0 &= ~(1 << WGM00);
	 TCCR0 |= (1 << WGM01);
#elif TIMER_MODE==PWM_PHASECORRECT
	 TCCR0 |= (1 << WGM00);
	 TCCR0 &= ~(1 << WGM01);
#elif TIMER_MODE==FASTPWM
	 TCCR0 |= (1 << WGM00);
	 TCCR0 |= (1 << WGM01);
#else
#error "TIMER0_mode has a wrong config"
#endif

	 TCCR0&=0xf8; //mask bit for prescaler

#if   TIMER_PRES == PRES_1024
	 TCCR0 |= (1<<CS02);
	 TCCR0 &= ~(1<<CS01);
	 TCCR0 |= (1<<CS00);

#elif TIMER_PRES == PRES_256
	 TCCR0 |= (1<<CS02);
	 TCCR0 &= ~(1<<CS01);
	 TCCR0 &= ~(1<<CS00);
#elif TIMER_PRES == PRES_64
	 TCCR0 &= ~(1<<CS02);
	 TCCR0 |= (1<<CS01);
	 TCCR0 |= (1<<CS00);
#elif TIMER_PRES == PRES_8
	 TCCR0 &= ~(1<<CS02);
	 TCCR0 |= (1<<CS01);
	 TCCR0 &= ~(1<<CS00);
#elif TIMER_PRES == PRES_NO
	 TCCR0 &= ~(1<<CS02);
	 TCCR0 &= ~(1<<CS01);
	 TCCR0 |= (1<<CS00);
#elif TIMER_PRES == NO_CLOCK_ SOURCE
	 TCCR0 &= ~(1<<CS02);
	 TCCR0 &= ~(1<<CS01);
	 TCCR0 &= ~(1<<CS00);
#elif TIMER_PRES == FALLING_EDGE
	 TCCR0 |= (1<<CS02);
	 TCCR0 |= (1<<CS01);
	 TCCR0 &= ~(1<<CS00);
#elif TIMER_PRES == RISING_EDGE
	 TCCR0 |= (1<<CS02);
	 TCCR0 |= (1<<CS01);
	 TCCR0 |= (1<<CS00);
#else
#error "TIMER0_PRES has a wrong config"
#endif
	 TCCR0&=0xCF; //mask bit for oc_mode
#if   OC_MODE == DISCONNECTED
	 TCCR0 &= ~(1<<COM01);
	 TCCR0 &= ~(1<<COM00);

#elif OC_MODE==SET;
#if TIMER_MODE==CTC
	 TCCR0 |= (1<<COM01);
	 TCCR0 |= (1<<COM00);
#endif
#elif OC_MODE==CLEAR;
#if TIMER_MODE==CTC
	 TCCR0 |= (1<<COM01);
	 TCCR0 &= ~(1<<COM00);
#endif
#elif OC_MODE==TOGGLE;
#if TIMER_MODE==CTC
	  TCCR0 &= ~(1<<COM01);
	  TCCR0 |= (1<<COM00);
#endif
#elif OC_MODE==INVERTED;
#if TIMER_MODE==(FASTPWM||PWM_PHASECORRECT)
	  TCCR0 |= (1<<COM01);
	  TCCR0 |= (1<<COM00);
#endif
#elif OC_MODE==NON_INVERTED;
#if TIMER_MODE==(FASTPWM||PWM_PHASECORRECT)
	  TCCR0 |= (1<<COM01);
	  TCCR0 &= ~(1<<COM00);
#endif
#else
#error "TIMER0_OC_MODE has a wrong config"
#endif

return Local_enuErrorState;
}
ES_t TIMER0_enuSetPreload(u8 Copy_u8Preload){
	ES_t Local_enuErrorState = ES_NOK;
	TCNT0=Copy_u8Preload;
	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}
//fun for interrupt
ES_t TIMER0_enuSetAsyncDelay(u32 Copy_u32Time,void (*Copy_pfunAppFun)(void*),void * Copy_pvidParameter){
	ES_t Local_enuErrorState = ES_NOK;

		f32 Local_f32TimeOvf=256 * ((f32)TIMER_PRES/TIMER_F_CPU); //cal Time of overflow
		f32 Local_f32NumOvf= Copy_u32Time/Local_f32TimeOvf;      // cal Number of overflow
		if((Local_f32NumOvf-(u32)Local_f32NumOvf)!=0.0){
			u32 Local_u32NumOvf_int=(u32)Local_f32NumOvf+1;
			Local_f32NumOvf=Local_f32NumOvf-(u32)Local_f32NumOvf;
			u8 Local_u8Preload=256-(256*Local_f32NumOvf);
			TCNT0=Local_u8Preload;
			 Global_u32NumOvf=Local_u32NumOvf_int;
			 Global_u8Preload=Local_u8Preload;}
			 else
			 	{
				 Global_u32NumOvf = (u32)Local_f32NumOvf;

			 	}

			 	if(Copy_pfunAppFun != NULL)
			 	{
			 		Timer0_ApFun_OVF= Copy_pfunAppFun;
			 		Timer0_Apvidparameter_OVF = Copy_pvidParameter;

			 	}
			 	else
			 	{
			 		Local_enuErrorState = ES_NULL_POINTER;
			 	}

			 	TIMSK |= (1 << TOIE0);

			 	return Local_enuErrorState;
		}


//fun busy wait

ES_t TIMER0_enuSetsyncDelay(u32 Copy_u32Time){
	ES_t Local_enuErrorState = ES_NOK;
	TIMSK&=~(1<<TOIE0); //disable for interrupt
	f32 Local_f32TimeOvf=256 * ((f32)TIMER_PRES/TIMER_F_CPU); //cal Time of overflow
	f32 Local_f32NumOvf= (f32)Copy_u32Time/Local_f32TimeOvf; // cal Number of overflow

	if((Local_f32NumOvf-(u32)Local_f32NumOvf)!=0.0){

		u32 Local_u32NumOvf_int=(u32)Local_f32NumOvf+1;
		Local_f32NumOvf=Local_f32NumOvf-(u32)Local_f32NumOvf;
		u8 Local_u8Preload=256-(256*Local_f32NumOvf);
		TCNT0=Local_u8Preload;

		while(Local_u32NumOvf_int){
			while(!((TIFR >> TOV0) & 1));
						TIFR |= (1 << TOV0);   //clear flag
						Local_u32NumOvf_int--;
		}
	}
		else {
			u32 Local_u32NumOvf_int=(u32)Local_f32NumOvf;
			while(Local_u32NumOvf_int){
					while(!((TIFR >> TOV0) & 1));
								TIFR |= (1 << TOV0);  //clear flag
								Local_u32NumOvf_int--;
				}
		}
	return Local_enuErrorState;
	}

/*ES_t TIMER0_enuDelayMilliSecondSyn(u32 Copy_u32DelayTime_ms)
{
	ES_t Local_enuErrorState = ES_NOK;

	f32 Local_f32TimeOverFlow = 256.0 * TIMER_PRES / TIMER_F_CPU; //cal Time of overflow
	f32 Local_f32Num_OVF_FLOAT = (f32)Copy_u32DelayTime_ms / Local_f32TimeOverFlow; // cal Number of overflow


	if((Local_f32Num_OVF_FLOAT - (u32)Local_f32Num_OVF_FLOAT) != 0.0)
	{
		u32 Local_u32Num_OVF_INT = (u32)Local_f32Num_OVF_FLOAT + 1;
		Local_f32Num_OVF_FLOAT = Local_f32Num_OVF_FLOAT - (u32)Local_f32Num_OVF_FLOAT;
		u8 Local_u8PreLoad = 256 - (256 * Local_f32Num_OVF_FLOAT);
		TCNT0 = Local_u8PreLoad;
		while(Local_u32Num_OVF_INT)
		{
			while(!((TIFR >> TOV0) & 1));
			TIFR |= (1 << TOV0);
			Local_u32Num_OVF_INT--;
		}
	}
	else
	{
		u32 Local_u32Num_OVF_INT = (u32)Local_f32TimeOverFlow;
		while(Local_u32Num_OVF_INT)
		{
			while(!((TIFR >> TOV0) & 1));
			TIFR |= (1 << TOV0); //Clear flag
			Local_u32Num_OVF_INT--;
		}
	}

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}
*/

ES_t TIMER0_enuGeneratePWM(u8 Copy_u8DutyCycle)
{
	ES_t Local_enuErrorState = ES_NOK;

	#if TIMER0_MODE == PWM_PHASECORRECT
	#if OC0_MODE == NON_INVERTED
	TIMER0_f32OC0Val = (Copy_u8DutyCycle * TIMER0_TOP_COUNTS) /100;
	Local_enuErrorState = ES_OK;
	#elif OC0_MODE == INVERTED
	TIMER0_f32OC0Value = (TIMER0_TOP_COUNTS - ((Copy_u8DutyCycle * TIMER0_TOP_COUNTS) / (100));
	Local_enuErrorState = ES_OK;
	#else
	#error "OC0 has a wrong config"
	#endif

	#elif TIMER0_MODE == FASTPWM
	#if OC0_MODE == NON_INVERTED
	TIMER0_f32OC0Value = (Copy_u8DutyCycle * TIMER0_NO_OVF_COUNTS) / 100
	Local_enuErrorState = ES_OK;
	#elif OC0_MODE == INVERTED
	TIMER0_f32OC0Value = (TIMER0_TOP_COUNTS - ((Copy_u8DutyCycle * TIMER0_NO_OVF_COUNTS) / 100));
	Local_enuErrorState = ES_OK;
	#else
	#error "OC0 has a wrong config"
	#endif
	#endif

	OCR0 = TIMER0_f32OC0Val;

	return Local_enuErrorState;
}
ES_t TIMER0_enuSetCTCVal(u8 Copy_u8CTC_Val){
ES_t Local_enuErrorState = ES_NOK;

	OCR0 = Copy_u8CTC_Val;
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;}

ES_t TIMER0_enuSetCALLBACK_CTC(void (*Copy_PFunApp)(void *), void *Copy_PParameterApp)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_PFunApp != NULL)
	{
		TIMER0_PFun_CTC = Copy_PFunApp;
		TIMER0_Pvidparameter_CTC = Copy_PParameterApp;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t TIMER0_enuEnableOVFInterrupt(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	TIMSK |= (1 << TOIE0);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t TIMER0_enuEnableCTCInterrupt(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	TIMSK |= (1 << OCIE0);
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}



ISR(VECT_TIMER0_CTC)
{
	if(TIMER0_PFun_CTC != NULL)
	{
		TIMER0_PFun_CTC((void *)TIMER0_Pvidparameter_CTC);
	}
}
ISR(VECT_TIMER0_OVF	)
{
	if(Timer0_ApFun_OVF != NULL)
	{
		static u32 Local_u32Counter = 0;
		Local_u32Counter++;
		if(Local_u32Counter == Global_u32NumOvf)
		{
			TCNT0 = Global_u8Preload;
			Timer0_ApFun_OVF((void *)Timer0_Apvidparameter_OVF);
			Local_u32Counter = 0;
		}
	}
}
