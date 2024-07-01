/*
 * EXTI_Prog.c
 *
 *  Created on: Feb 5, 2024
 *      Author: samar ibrahim
 */

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "EXTI_priv.h"
#include "EXTI_config.h"

#include "../interrupt.h"

static volatile void (*EXTI_ApfunINTFun[3])(void*) = {NULL,NULL,NULL};
void * EXTI_ApvidGenericparameter[3] = {NULL,NULL,NULL};

// fun to initialize the external interrupt take pointer to  id of interrupt

ES_t EXTI_enuInit (EXTI_t * Copy_pstrEXTIConfig){
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_pstrEXTIConfig!=NULL){
		u8 Local_u8Iter=0;
    for (Local_u8Iter =0; Local_u8Iter < 3 ; Local_u8Iter++)
    {
    	if (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8State == ENABLE)
    	{
    		switch (Local_u8Iter)
    						{
    		case INT0:
    			 MCUCR &=~ (3<<0);
    			 GICR|=(1<<6);

    			switch (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8SenseLevel)
    			{
                     case LOW_LEVEL:
                    	 break;
                     case ANY_LOGIC:
                    	 MCUCR |=(1<<0);
                    	 break;
                     case FALLING_EDGE:
                    	 MCUCR |=(1<<1);
                    	 break;
                     case RISING_EDGE:
                    	 MCUCR |=(3<<0);
                    	 break;
                    default:
						Local_enuErrorState = ES_OUT_OF_RANGE;
					}
					break;

    		case INT1:
    			MCUCR &=~ (3<<2);
    			GICR |= (1<<7);

    			switch (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8SenseLevel)
    			{
    	         case LOW_LEVEL:
    	        	 break;
    	         case ANY_LOGIC:
    	        	 MCUCR |=(1<<2);
    	        	 break;

    	         case FALLING_EDGE:
    	        	 MCUCR |=(1<<3);
    	        	 break;

    	         case RISING_EDGE:
    	        	 MCUCR |=(3<<2);
    	        	 break;

    	        default:
    				Local_enuErrorState = ES_OUT_OF_RANGE;
    			}
    			break;

    		case INT2:
    			MCUCSR &=~(1<<6);
    			GICR |= (1<<5);

    			switch (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8SenseLevel)
    		   	{
                 case FALLING_EDGE:
                	 break;

                 case RISING_EDGE:
                	 MCUCSR |= (1<<6);
                	 break;

                default:
  			    Local_enuErrorState = ES_OUT_OF_RANGE;
  		        }
  		        break;

              default:
              Local_enuErrorState = ES_OUT_OF_RANGE;
    						}}}}
	else {
		ES_t Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


/*** fun to set sense level
     take id ,sense level                              ***/
ES_t EXTI_enuSetSenseLevel(u8 Copy_u8EXTI_ID , u8 Copy_u8SenseLevel){
	ES_t Local_enuErrorState = ES_NOK;
 if(Copy_u8EXTI_ID < 3){
	 if(Copy_u8EXTI_ID ==INT0){
		 MCUCR &=~ (3<<0);
			switch (Copy_u8SenseLevel)
		    			{
		                     case LOW_LEVEL:
		                    	 break;
		                     case ANY_LOGIC:
		                    	 MCUCR |=(1<<0);
		                    	 break;
		                     case FALLING_EDGE:
		                    	 MCUCR |=(1<<1);
		                    	 break;
		                     case RISING_EDGE:
		                    	 MCUCR |=(3<<0);
		                    	 break;
		                    default:
								Local_enuErrorState = ES_OUT_OF_RANGE;
							}
	 }
	 else if(Copy_u8EXTI_ID ==INT1){
		 MCUCR &=~ (3<<2);

		     			switch (Copy_u8SenseLevel)
		     			{
		     	         case LOW_LEVEL:
		     	        	 break;
		     	         case ANY_LOGIC:
		     	        	 MCUCR |=(1<<2);
		     	        	 break;

		     	         case FALLING_EDGE:
		     	        	 MCUCR |=(1<<3);
		     	        	 break;

		     	         case RISING_EDGE:
		     	        	 MCUCR |=(3<<2);
		     	        	 break;

		     	        default:
		     				Local_enuErrorState = ES_OUT_OF_RANGE;
		     			}
	 }
	 else if(Copy_u8EXTI_ID ==INT2){
		 MCUCSR &=~(1<<6);
		     			GICR |= (1<<5);

		     			switch (Copy_u8SenseLevel)
		     		   	{
		                  case FALLING_EDGE:
		                 	 break;

		                  case RISING_EDGE:
		                 	 MCUCSR |= (1<<6);
		                 	 break;

		                 default:
		   			    Local_enuErrorState = ES_OUT_OF_RANGE;
		   		        }
		 }
 }
 else{
	 ES_t Local_enuErrorState = ES_OUT_OF_RANGE;
 }
	return Local_enuErrorState;
}

/*** fun to enable specific the interrupt
                      ***/
ES_t EXTI_enuEnableINT(u8 Copy_u8EXTI_ID){
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_u8EXTI_ID < 3)
		{
			if (Copy_u8EXTI_ID ==INT0)
			{
				GICR |= (1<<6);
			}
			else if (Copy_u8EXTI_ID ==INT1)
			{
				GICR |= (1<<7);
			}
			else if (Copy_u8EXTI_ID ==INT2)
			{
				GICR |= (1<<5);
			}
		}

	return Local_enuErrorState;
}

/***   fun to disable specific interrupt
                      ***/
ES_t EXTI_enuDisableINT(u8 Copy_u8EXTI_ID){
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_u8EXTI_ID < 3)
		{
			if (Copy_u8EXTI_ID ==INT0)
			{
				GICR &= ~(1<<6);
			}
			else if (Copy_u8EXTI_ID ==INT1)
			{
				GICR&= ~(1<<7);
			}
			else if (Copy_u8EXTI_ID ==INT2)
			{
				GICR &= ~(1<<5);
			}
		}

	return Local_enuErrorState;
}

 /***  call back fun to use function that exist in application level
                          ***/

ES_t EXTI_enuCallBack(volatile void (*Copy_pfunAppFun)(void*) , volatile void * Copy_pvidParameter , u8 Copy_u8EXTI_ID)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_pfunAppFun != NULL && Copy_u8EXTI_ID <3)
	{
		EXTI_ApfunINTFun[Copy_u8EXTI_ID]=Copy_pfunAppFun;
		EXTI_ApvidGenericparameter[Copy_u8EXTI_ID] = Copy_pvidParameter;
	}

	return Local_enuErrorState;
}



ISR(VECT_INT0)
{
	if (EXTI_ApfunINTFun[0] != NULL)
	{
		EXTI_ApfunINTFun[0] (EXTI_ApvidGenericparameter[0]);
	}
}

ISR(VECT_INT1)
{
	if (EXTI_ApfunINTFun[1] != NULL)
	{
		EXTI_ApfunINTFun[1] (EXTI_ApvidGenericparameter[1]);
	}
}

ISR(VECT_INT2)
{
	if (EXTI_ApfunINTFun[2] != NULL)
	{
		EXTI_ApfunINTFun[2] (EXTI_ApvidGenericparameter[2]);
	}
}
