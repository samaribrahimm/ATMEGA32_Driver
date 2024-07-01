/*
 * Thermistor_config.h
 *
 *  Created on: Feb 21, 2024
 *      Author: samar ibrahim
 */

#ifndef HAL_THERMISTOR_THERMISTOR_CONFIG_H_
#define HAL_THERMISTOR_THERMISTOR_CONFIG_H_
#include"../../LIB/errorStates.h"
#include"../../LIB/stdTypes.h"


#include"../../MCAL/ADC/ADC_int.h"
#define LM35NUM		1
typedef struct {
	u8 LM35_postiveChannel;
	u8 LM35_negativeChannel;
}Themistor_t;



#endif /* HAL_THERMISTOR_THERMISTOR_CONFIG_H_ */
