/*
 * mainpp.cpp
 *
 *  Created on: Jul 8, 2025
 *      Author: USER
 */

#include "encoder.h"
#include "mainpp.h"
#include "control.h"
#include "servo.h"
#include "DC_motor.h"
#include <cmath>

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;

DC_motor Motor1(&htim3,GPIOA,GPIO_PIN_9,&htim8,TIM_CHANNEL_1);

float speeds = 0;
float range = 1;
float add = 0.01;

void main_function(){
	Motor1.setup();
	HAL_TIM_Base_Start_IT(&htim6);
//	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
//    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);
	while(1){
		Motor1.setspeed(speeds);
		Motor1.PI_run();
		speeds += add;
		if(abs(speeds) > range){
			add*=-1;
		}
		HAL_Delay(5);
	}
}
int ms = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM6){
		Motor1.update_speed(1);
		Motor1.PI_run();
		ms++;
	}
}
