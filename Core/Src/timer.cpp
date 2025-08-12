/*
 * timer.cpp
 *
 *  Created on: Aug 12, 2025
 *      Author: USER
 */

#include "timer.h"
#include "stm32g4xx_hal.h"
static int delay_count = 0;
int t_ms = 0;
void wait(int time,TIM_HandleTypeDef *htim){//time單位為ms

	while(delay_count < time){
		HAL_TIM_Base_Start_IT(htim);
		//delay_count++;
	}
	//HAL_TIM_Base_Stop_IT(htim);
	delay_count = 0;

}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		t_ms++;
		delay_count++;
	}
}

