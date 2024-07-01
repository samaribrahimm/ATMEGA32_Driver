/*
 * TIMER_init.h
 *
 *  Created on: Feb 29, 2024
 *      Author: samar ibrahim
 */

#ifndef MCAL_TIMER0_TIMER_INT_H_
#define MCAL_TIMER0_TIMER_INT_H_

ES_t TIMER0_enuInit(void);
ES_t TIMER0_enuDisable(u8 Copy_u8TimerId);
ES_t TIMER0_enuSetPreload(u8 Copy_u8Preload);
ES_t TIMER0_enuSetAsyncDelay(u32 Copy_u32Time_ms,void (*Copy_pfunAppFun)(void*),void * Copy_pvidParameter); //interrupt_overflow(call back)
ES_t TIMER0_enuDelayMilliSecondSyn(u32 Copy_u32DelayTime_ms); //polling

ES_t TIMER0_enuSetCALLBACK_CTC(void (*Copy_PFunApp)(void *), void *Copy_PParameterApp);
ES_t TIMER0_enuSetCTCVal(u8 Copy_u8CTC_Val);

ES_t TIMER0_enuGeneratePWM(u8 Copy_u8DutyCycle);
ES_t TIMER0_enuSetsyncDelay(u32 Copy_u32Time);
/*





ES_t TIMER0_enuEnableOVFInterrupt(void);

ES_t TIMER0_enuEnableCTCInterrupt(void);*/


#endif /* MCAL_TIMER0_TIMER_INT_H_ */
