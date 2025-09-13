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

Servo servo_turn = {&htim3, TIM_CHANNEL_1, Servo::GBD300T};
Servo servo_gripper = {&htim1, TIM_CHANNEL_2, Servo::GBD300T};
Servo servo_left = {&htim1, TIM_CHANNEL_4, Servo::GBD300T};
Servo servo_right = {&htim1, TIM_CHANNEL_3, Servo::GBD300T};
Servo servo_forward = {&htim1, TIM_CHANNEL_1, Servo::GBD1800T};
int tt = 0;
//通訊

bool isTop = 0;
bool table_isTouch = 0;
bool casecadeLift = true;
bool initialized = false;

float speeds = 0;
float turn = 0;
float angle = 0; //測試用
float angle_2 = 0;
float high1= 0.0f;
int delay_count = 0;
int elevator_type = 0;
int ms = 0;

//casecadeLift
float total_turns = 3.01147461;  // 用來記錄總步數
float total_high = 335; // 最大高度差
float mm_per_turn = total_high / total_turns; // 每步對應的公分數
float height = 0.0f;
float target_turns = 0.0f;
float pp = 0;
//forward
float angle_per_mm = 880/305.0;
int zeroPointAngle = 300;  //32

//turn
float _current_y = 0.0f;
float _current_theta = 0.0f;

void setup_all(){
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	ms++;
	servo_forward.setup(920);
	servo_turn.setup(261);
	Motor_updown.setup();
	initialized = true;
	speeds = -0.5;
	wait(3000, &htim2);
	initialized = false;
	speeds = 0.5;
	wait(1500, &htim2);


	wait(5000, &htim2);
	servo_gripper.setup(0);
	servo_right.setup(150);
	servo_left.setup(0);
	servo_forward.turnTo(300); //920---40 底

	ROS1::init();
	//HAL_TIM_Base_Start_IT(&htim2);


}
void main_function(){
	setup_all();

	//ROS1::init();
	while(1){
		//
//		wait(1000, &htim2);
		//
		//forwardToPoint(pp);
		//servo_forward.turnTo(angle, 3000);
		//servo_gripper.turnTo(angle);
//		wait(1000, &htim2);

		//servo_turn.setup(aljjojojoj);
		//ROS1::_pub_gripper();
		ROS1::spinCycle();
		// ROS1::_pub_gripper();
		//mission_3();
		//middleTurn(angle);


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
		height = 445 + turn * mm_per_turn;
		Motor_updown.PI_run();
		Motor_updown.update_speed(-1);
		Motor_updown.setspeed(speeds);
		ms++;

		//ROS1::_pub_elevator();
	}
	if(htim->Instance == TIM7){
		ROS1::_pub_gripper();
		ROS1::_pub_touch();
		ROS1::_pub_theta();
		ROS1::_pub_y();
		//s++;
		}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	switch(GPIO_Pin){
		case GPIO_PIN_7: //第一節
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_RESET){
				tt = 7;
				elevator_type = 1;
				casecadeLift = false;  // 重置初始化狀態
				//speeds = 0;
				//turn1 = turn;
				//wait(5000, &htim2);
			}
			else if(HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_SET){
				casecadeLift = true;
			}
			//Motor_updown.setspeed(speeds);
			break;
		case GPIO_PIN_8: //第二節
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_RESET){
				elevator_type = 2;
				tt = 8;
				//turn2 = turn;

				//wait(5000, &htim2);
				//HAL_Delay(1000);
			}
			else if(HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_SET){
				elevator_type = 1;
			}

			//Motor_updown.setspeed(speeds);
			break;
		case GPIO_PIN_9: // 桌面
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_RESET){
				tt = 9;
				speeds = 0;
				table_isTouch = 1;
				//table_isTouch = 0;
			}
			else if (HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_SET){
				table_isTouch = 0;
			}

			break;
		case GPIO_PIN_4: //夾爪下
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_RESET){
				tt = 4;
				speeds = 0;
				elevator_type = -1;
				turn = 0;
			}
			else if(HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_SET){
				elevator_type = 0;
			}

			break;
		case GPIO_PIN_5: //夾爪上
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_RESET){
				tt = 5;
				if(initialized == false){
					initialized = true;  // 重置初始化狀態
					speeds = 0;
				}
				isTop = 1;
				//speeds = 0;
				elevator_type = 1;
				
			}
			else if (HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_SET){
				isTop = 0;
			}

			break;
		case GPIO_PIN_14: //casecade highest
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) == GPIO_PIN_RESET){
				tt = 14;
				isTop = 3;
				speeds = 0;
				elevator_type = 3;

			}
			else if (HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) == GPIO_PIN_SET){
				isTop = 0;

			}

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
