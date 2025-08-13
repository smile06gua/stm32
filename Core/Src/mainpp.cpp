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
#include "timer.h"
#include <cmath>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;

DC_motor Motor_forword = {&htim3, GPIOA, GPIO_PIN_9, &htim8, TIM_CHANNEL_1};
DC_motor Motor_updown = {&htim4, GPIOA, GPIO_PIN_10, &htim8, TIM_CHANNEL_2};


servo servo_gripper = {&htim1, TIM_CHANNEL_3};
servo servo_trun = {&htim1, TIM_CHANNEL_2};


float speeds = 0;
float range = 1;
float add = 0.01;
float angle = 30;
float high= 0.0;
int gripperHighest = 0;
int gripperLowest = 0;
void setup_all(){
	servo_gripper.setup();
	Motor_forword.setup();
	Motor_updown.setup();
}
void main_function(){
	setup_all();

	while(1){
		/*motor_updown
		*/
		if(gripperHighest == 0){
			motor_updown.setspeed(speeds);
			motor_updown.PI_run();
		}


		/*servo_gripper
		servo_gripper.update_pos(angle, 1);
		servo_gripper.run();
		wait(3000, &htim2);
		servo_gripper.update_pos(300, 1);
		servo_gripper.run();
		wait(3000, &htim2);
		*/
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	switch(GPIO_Pin){
		case GPIO_PIN_13:
			gripperHighest = 1;
			gripperLowest = 0;
			high = 100;
			Motor_updown.setspeed(0);
			break;
		case GPIO_PIN_12:
			gripperLowest = 1;
			gripperHighest = 0;
			high = 0;
			Motor_updown.setspeed(0);
			break;

	}
}
/*
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
*/
