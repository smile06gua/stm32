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
#include "mission.h"
#include "DC_motor.h"
#include "stm32g4xx_hal.h"
//#include "timer.h"
#include <cmath>
#include <cstdint>
#include <cstdlib>


//DC_motor Motor_forword = {&htim3, GPIOA, GPIO_PIN_9, &htim8, TIM_CHANNEL_1};
DC_motor Motor_updown = {&htim4, GPIOA, GPIO_PIN_10, &htim8, TIM_CHANNEL_2};

Servo servo_turn = {&htim3, TIM_CHANNEL_1};
Servo servo_gripper = {&htim1, TIM_CHANNEL_2};
Servo servo_left = {&htim1, TIM_CHANNEL_3};
Servo servo_right = {&htim1, TIM_CHANNEL_4};
Servo servo_forward = {&htim1, TIM_CHANNEL_1};

bool initialized = true;
float speeds = 0;
float range = 1;
float add = 0.01;
float angle = 150;
float angle_2 = 150;
float high= 0.0;
int delay_count = 0;
int gripperHighest = 0;
int gripperLowest = 0;
int32_t total_steps = 0;  // 用來記錄總步數


void setup_all(){
	servo_gripper.setMaxAngle(300);
	servo_gripper.setup(0);
	servo_right.setup(0);
	servo_left.setup(0);
	servo_forward.setMaxAngle(1800);
	servo_forward.setup(90);
	servo_turn.setup(0);
	Motor_updown.setup();
}
void main_function(){
	setup_all();

	while(1){
		mission_2();
		//mission_2();



	}
}


void wait(int time,TIM_HandleTypeDef *htim){//time單位為ms

	HAL_TIM_Base_Start_IT(htim);
	while(delay_count < time){
	}

	HAL_TIM_Base_Stop_IT(htim);

	delay_count = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		delay_count++;
        Motor_updown.update_speed(1);  // 定期更新encoder計數
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	switch(GPIO_Pin){
		case GPIO_PIN_13:
			if (HAL_GPIO_ReadPin(GPIOC, GPIO_Pin) == GPIO_PIN_RESET){
				speeds = 0;
				gripperHighest = 1;
				gripperLowest = 0;
				high = 100;
			}
			//Motor_updown.setspeed(speeds);
			break;
		case GPIO_PIN_12:
			if (HAL_GPIO_ReadPin(GPIOC, GPIO_Pin) == GPIO_PIN_RESET){
				initialized = false;  // 重置初始化狀態
				speeds = -1;
				gripperHighest = 0;
				gripperLowest = 1;
				high = 0;
				total_steps = 0;
				//HAL_Delay(1000);
			}

			//Motor_updown.setspeed(speeds);
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
