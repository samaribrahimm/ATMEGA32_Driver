/*
 * Thermistor_config.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Samar ibrahim
 */

#include"Thermistor_config.h"
#include"Thermistor_priv.h"
#include "../../MCAL/ADC/ADC_int.h"
Themistor_t LM35_AstrEXTIConfig [LM35NUM] =
{
		{ADC0, NOTCONNECTED},

};
