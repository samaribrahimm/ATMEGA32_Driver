/*
 * Thermistor_int.h
 *
 *  Created on: Feb 21, 2024
 *      Author: user
 */

#ifndef HAL_THERMISTOR_THERMISTOR_INT_H_
#define HAL_THERMISTOR_THERMISTOR_INT_H_

ES_t Thermistor_enuInit(Themistor_t* PstrLM35config);
ES_t Themistor_enuGetTemp(u8 Copy_u8_LM35_ID,f32 *Copy_f32Temp);

#endif /* HAL_THERMISTOR_THERMISTOR_INT_H_ */
