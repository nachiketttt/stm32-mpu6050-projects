/*
 * app_callback.c
 *
 *  Created on: May 4, 2026
 *      Author: nachiket
 */
#include "main.h"

extern uint32_t g_counter;
extern volatile uint32_t g_channel_1_state;
extern volatile uint32_t g_channel_2_state;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	g_counter=0;
	g_channel_1_state=__HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);


	g_channel_2_state=__HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_2);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)
		g_channel_1_state=0;
	if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
		g_channel_2_state=0;
}

void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_ErrorCallback could be implemented in the user file
   */
}
