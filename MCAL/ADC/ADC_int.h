/*
 * ADC_int.h
 *
 *  Created on: Feb 17, 2024
 *      Author: samar ibrahim
 */


#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

ES_t ADC_enuInit(void);
ES_t ADC_enuEnable(void);
ES_t ADC_enuDisable(void);
ES_t ADC_enuStartConversion(void);
ES_t ADC_enuSelectChannel(u8 Copy_Channel_ID);
ES_t ADC_enuPollingSystem(void);
ES_t ADC_enuReadHighValue(u8* Copy_pu8Value);
ES_t ADC_enuReadValue(u16* Copy_pu16Value);
ES_t ADC_enuCallBack(void(*Copy_pfunAppFun)(void*),void*Copy_pviAppParameter);
ES_t ADC_enuEnableTriggerMode(u8 Copy_u8TriggerSource);
ES_t ADC_enuDisableTriggerMode(void);
ES_t ADC_enuEnableInterruptrMode(void);
ES_t ADC_enuDisableInterruptrMode(void);
//channel
#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

// TriggerMode
#define FREE_RUNNING_MODE				1
#define ANALOG_COMPARATOR			    2
#define EXTI0_TRIG					    3
#define TIMER0_COMPARE_MATCH_TRIG	    4
#define TIMER0_OVERFLOW_TRIG		    5
#define TIMER1_COMPARE_MATCH_TRIG	    6
#define TIMER1_OVERFLOW_TRIG		    7
#define TIMER1_CAPUTRE_TRIG			    8
#endif /* MCAL_ADC_ADC_INT_H_ */
