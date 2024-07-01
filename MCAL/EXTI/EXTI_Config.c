/*
 * EXTI_Config.c
 *
 *  Created on: Feb 5, 2024
 *      Author: samar ibrahim
 */

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "EXTI_priv.h"
#include "EXTI_config.h"

EXTI_t EXTI_AstrEXTIConfig [3] =
{
		{ENABLE, RISING_EDGE},
		{DISABLE},
		{DISABLE}
};
