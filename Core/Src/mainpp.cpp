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
#include "ros1.h"
//#include "timer.h"
#include <cmath>
#include <cstdint>
#include <cstdlib>

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
//DC_motor Motor_forword = {&htim3, GPIOA, GPIO_PIN_9, &htim8, TIM_CHANNEL_1};
DC_motor Motor_updown = {&htim4, GPIOA, GPIO_PIN_10, &htim8, TIM_CHANNEL_2,0,4,12};

Servo servo_turn = {&htim3, TIM_CHANNEL_3, Servo::GBD1800T};
Servo servo_gripper = {&htim1, TIM_CHANNEL_2, Servo::GBD300T};
Servo servo_left = {&htim1, TIM_CHANNEL_4, Servo::GBD300T};
Servo servo_right = {&htim1, TIM_CHANNEL_1, Servo::GBD300T};
Servo servo_forward = {&htim1, TIM_CHANNEL_1, Servo::GBD1800T};

//通訊
bool girpperIsGet = 0;
bool basketIsGet = 0;


bool casecadeLift = true;
bool initialized = true;
float speeds = -0.5;
float turn = 0;
float range = 1;
float add = 0.01;
float angle = 0;
float angle_2 = 0;
float high1= 0.0f;
int delay_count = 0;
int gripperHighest = 0;
int gripperLowest = 0;
int ms = 0;
float total_turns = 2.746;  // 用來記錄總步數
float total_high = 302; // 最大高度差
float mm_per_turn = total_high / total_turns; // 每步對應的公分數
float turn1, turn2;
float height = 0.0f;
float target_turns = 0.0f;
void setup_all(){
	servo_gripper.setup(0);
	servo_right.setup(0);
	servo_left.setup(0);
	servo_forward.setup(90);
	servo_turn.setup(0);
	Motor_updown.setup();
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	ms++;
}
void main_function(){
	setup_all();
	//ROS1::init();
	while(1){
		//ROS1::_pub_gripper();
		//ROS1::spinCycle();
		// ROS1::_pub_gripper();
		mission_2();



	}
}


void wait(int time,TIM_HandleTypeDef *htim){//time單位為ms

	HAL_TIM_Base_Start_IT(htim);
	while(delay_count < time){
	}

	HAL_TIM_Base_Stop_IT(htim);

	delay_count = 0;
}
float s;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		delay_count++;
	}
	if(htim->Instance == TIM6){

		Motor_updown.PI_run();
		Motor_updown.update_speed(-1);
		Motor_updown.setspeed(speeds);
		ms++;
	}
	if(htim->Instance == TIM7){

			//ms++;
		}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	switch(GPIO_Pin){
		case GPIO_PIN_15: //up
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) == GPIO_PIN_RESET){
				//casecadeLift = false;  // 重置初始化狀態
				speeds = 0;
				turn1 = turn;
				//wait(5000, &htim2);
			}
			//Motor_updown.setspeed(speeds);
			break;
		case GPIO_PIN_14: //down
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) == GPIO_PIN_RESET){

				speeds = 0;
				turn = 0;
				//turn2 = turn;
				initialized = false;  // 重置初始化狀態
				//wait(5000, &htim2);
				//HAL_Delay(1000);
			}

			//Motor_updown.setspeed(speeds);
			break;
		case GPIO_PIN_10:
			if (HAL_GPIO_ReadPin(GPIOC, GPIO_Pin) == GPIO_PIN_RESET){

				//speeds = 0;
				//wait(5000, &htim2);
				//HAL_Delay(1000);
			}

			break;
		case GPIO_PIN_13:
			wait(1000, &htim2);
			if (HAL_GPIO_ReadPin(GPIOC, GPIO_Pin) == GPIO_PIN_RESET){
				//servo_gripper.turnTo(280);
			}

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
