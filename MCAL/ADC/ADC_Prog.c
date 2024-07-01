/*
 * ADC_Prog.c
 *
 *  Created on: Feb 17, 2024
 *      Author: samar ibrahim
 */
#include"../../LIB/errorStates.h"
#include"../../LIB/stdTypes.h"

#include"ADC_Priv.h"
#include"ADC_Config.h"
#include"../interrupt.h"

static volatile void (*ADC_PFuncISRFunc)(void *) = NULL;
static volatile void *ADC_PvidISRParameter = NULL;
ES_t ADC_enuInit(void){
	ES_t Local_enuErrorState = ES_NOK;

	ADMUX&=0x3F; //mask two bits of ADC_VREF (BIT6,7)
//VREF
#if   ADC_VREF==AVCC
	  ADMUX|=(MASK_BIT<<BIT6);
#elif ADC_VREF==AVREF
		ADMUX|=0x3F;
#elif ADC_VREF==INTERNAL_VREF
	  ADMUX|=0xC0;
#else
#error "ADC_VREF has a wrong selection"
#endif
 //CHOOSE ADJUSTMENT
	ADMUX &= ~(MASK_BIT <<BIT5);
#if   ADC_ADJUST==RIGHT_ADJUST
	   ADMUX&=~(MASK_BIT<<BIT5);
#elif ADC_ADJUST==LEFT_ADJUST
		ADMUX|=(MASK_BIT<<BIT5);

#else
#error "ADC_Adjustment has a wrong selection"
#endif

 //CHOOSE ADC_prescaler
		 ADCSRA &= 0xF8; //mask the first 3 bits in this register
#if   ADC_PRESCALER==DIVISION_FACTOR_2
		 ADCSRA &= 0xF8;
#elif ADC_PRESCALER==DIVISION_FACTOR_4
		 ADCSRA |=(MASK_BIT<<BIT2);
#elif ADC_PRESCALER==DIVISION_FACTOR_8
		 ADCSRA |=(MASK_BIT<<BIT0);
		 ADCSRA |=(MASK_BIT<<BIT1);
#elif ADC_PRESCALER==DIVISION_FACTOR_16
		 ADCSRA |=(MASK_BIT<<BIT2);
#elif ADC_PRESCALER==DIVISION_FACTOR_32
		 ADCSRA |=(MASK_BIT<<BIT0);
		 ADCSRA |=(MASK_BIT<<BIT2);
#elif ADC_PRESCALER==DIVISION_FACTOR_64
		 ADCSRA |=(MASK_BIT<<BIT0);
		 ADCSRA |=(MASK_BIT<<BIT2);
#elif ADC_PRESCALER==DIVISION_FACTOR_128
		 ADCSRA |=(MASK_BIT<<BIT0);
		 ADCSRA |=(MASK_BIT<<BIT1);
		 ADCSRA |=(MASK_BIT<<BIT2);

#else
#error "ADC_Adjustment has a wrong selection"
#endif


	return Local_enuErrorState ;
}
ES_t ADC_enuEnable(void){
	ES_t Local_enuErrorState =ES_NOK;
	 ADCSRA |=(MASK_BIT<<BIT7);
	return Local_enuErrorState ;
}
ES_t ADC_enuDisable(void){
	ES_t Local_enuErrorState =ES_NOK;
	 ADCSRA &=~(MASK_BIT<<BIT7);
	return Local_enuErrorState ;
}
ES_t ADC_enuStartConversion(void){
	ES_t Local_enuErrorState =ES_NOK;
		 ADCSRA |=(MASK_BIT<<BIT6);
		return Local_enuErrorState ;
}
ES_t ADC_enuSelectChannel(u8 Copy_Channel_ID){
	ES_t Local_enuErrorState =ES_NOK;
ADMUX&=0xF0; //mask the first 4 bits
ADMUX|=Copy_Channel_ID ;
return Local_enuErrorState ;

}
ES_t ADC_enuPollingSystem(void){
	ES_t Local_enuErrorState =ES_NOK;

		while(!((ADCSRA >> BIT4) & MASK_BIT)); //Busy Wait until flag is set


		ADCSRA |= (MASK_BIT << BIT4); //Clear flag

	return Local_enuErrorState ;
}
ES_t ADC_enuReadHighValue(u8* Copy_pu8Value){
	ES_t Local_enuErrorState =ES_NOK;
#if ADC_ADJUST==LEFT_ADJUST
	 *Copy_pu8Value=ADCH;
#elif ADC_ADJUST==RIGHT_ADJUST
	 *Copy_pu8Value=(ADCL>>2);
	 *Copy_pu8Value|=(ADCH<<6);
#else
#error "ADC_Adjustment has a wrong selection"
#endif
	return Local_enuErrorState ;
}
ES_t ADC_enuReadValue(u16* Copy_pu16Value){
	ES_t Local_enuErrorState =ES_NOK;
#if ADC_ADJUST==LEFT_ADJUST
	*Copy_pu16ReadValue  = ((u16)ADCL >> 6);
	*Copy_pu16ReadValue |= ((u16)ADCH << 2);
#elif ADC_ADJUST==RIGHT_ADJUST
	*Copy_pu16Value=((u16)ADCL);
	*Copy_pu16Value|=((u16)ADCH<<8);
#else
#error "ADC_Adjustment has a wrong selection"
#endif
	return Local_enuErrorState ;
}

ES_t ADC_enuEnableTriggerMode(u8 Copy_u8TriggerSource){
	ES_t Local_enuErrorState =ES_NOK;

	ADCSRA&=~(MASK_BIT<<BIT5); //Clear bit
	SFIOR &=0x1F; //Mask The last 3bits
	switch(Copy_u8TriggerSource){
	case FREE_RUNNING_MODE:
		SFIOR&=~(MASK_BIT<<BIT5);
		SFIOR&=~(MASK_BIT<<BIT6);
		SFIOR&=~(MASK_BIT<<BIT7);
    break;
	case ANALOG_COMPARATOR:
		SFIOR|=(MASK_BIT<<BIT5);
		SFIOR&=~(MASK_BIT<<BIT6);
		SFIOR&=~(MASK_BIT<<BIT7);
    break;
	case EXTI0_TRIG	:
		SFIOR&=~(MASK_BIT<<BIT5);
		SFIOR|=(MASK_BIT<<BIT6);
		SFIOR&=~(MASK_BIT<<BIT7);
	break;
	case TIMER0_COMPARE_MATCH_TRIG:
		SFIOR|=(MASK_BIT<<BIT5);
		SFIOR|=(MASK_BIT<<BIT6);
		SFIOR&=~(MASK_BIT<<BIT7);
	break;
	case TIMER0_OVERFLOW_TRIG:
		SFIOR&=~(MASK_BIT<<BIT5);
		SFIOR&=~(MASK_BIT<<BIT6);
		SFIOR|=(MASK_BIT<<BIT7);
	break;
	case TIMER1_COMPARE_MATCH_TRIG:
		SFIOR|=(MASK_BIT<<BIT5);
		SFIOR&=~(MASK_BIT<<BIT6);
		SFIOR|=(MASK_BIT<<BIT7);
	break;
	case TIMER1_OVERFLOW_TRIG	:
		SFIOR&=~(MASK_BIT<<BIT5);
		SFIOR|=(MASK_BIT<<BIT6);
		SFIOR|=(MASK_BIT<<BIT7);
	break;
	case TIMER1_CAPUTRE_TRIG	:
		SFIOR|=(MASK_BIT<<BIT5);
		SFIOR|=(MASK_BIT<<BIT6);
		SFIOR|=(MASK_BIT<<BIT7);
	break;
	default:
	Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}

	ADCSRA |= (MASK_BIT << BIT5);                  //set bit for enable trigger

	return Local_enuErrorState ;
}
ES_t ADC_enuDisableTriggerMode(void){
	ES_t Local_enuErrorState =ES_NOK;
	ADCSRA&=~(MASK_BIT<<BIT5); //Clear bit
	return Local_enuErrorState ;
}
ES_t ADC_enuEnableInterruptrMode(void){
	ES_t Local_enuErrorState =ES_NOK;
	ADCSRA |= (MASK_BIT <<BIT3);

	return Local_enuErrorState ;
}
ES_t ADC_enuDisableInterruptrMode(void){
	ES_t Local_enuErrorState =ES_NOK;
	ADCSRA &= ~(MASK_BIT << BIT3);

	return Local_enuErrorState ;
}
ES_t ADC_enuCallBack(volatile void(*Copy_pfunAppFun)(void*),volatile void*Copy_pviAppParameter)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pfunAppFun != NULL)
	{
		ADC_PFuncISRFunc = Copy_pfunAppFun;
		ADC_PvidISRParameter = Copy_pviAppParameter;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}

ISR(VECT_ADC)
{
	if(ADC_PFuncISRFunc != NULL)
	{
		ADC_PFuncISRFunc(ADC_PvidISRParameter);
	}
}
