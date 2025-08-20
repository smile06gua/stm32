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

using namespace Jason;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;

//DC_motor Motor_forword = {&htim3, GPIOA, GPIO_PIN_9, &htim8, TIM_CHANNEL_1};
DC_motor Motor_updown = {&htim4, GPIOA, GPIO_PIN_10, &htim8, TIM_CHANNEL_2};

Servo servo_turn = {&htim1, TIM_CHANNEL_1};
Servo servo_gripper = {&htim1, TIM_CHANNEL_2};
Servo servo_left = {&htim1, TIM_CHANNEL_3};
Servo servo_right = {&htim1, TIM_CHANNEL_4};
Servo servo_forward = {&htim3, TIM_CHANNEL_1};

static bool initialized = true;
float speeds = 0;
float range = 1;
float add = 0.01;
float angle = 150;
float angle_2 = 150;
float high= 0.0;
int delay_count = 0;
int gripperHighest = 0;
int gripperLowest = 0;
static int32_t total_steps = 0;  // 用來記錄總步數

void wait(int ,TIM_HandleTypeDef*);
void mission_1();
void mission_2();
void mission_3();
void mission_4();

void setup_all(){
	servo_gripper.setup(0);
	servo_right.setup(0);
	servo_left.setup(0);
	servo_forward.setup(0);
	servo_turn.setup(0);
	Motor_updown.setup();
}
void main_function(){
	setup_all();

	while(1){
		mission_3();
		//mission_2();



	}
}

void mission_1(){

}

void mission_2(){
	// 夾咖啡杯
	/*servo_gripper*/
	servo_gripper.update_pos(0, 1);  //off
	servo_gripper.run();
	wait(1000, &htim2);
	servo_gripper.update_pos(300, 1);  //open
	servo_gripper.run();
	wait(1000, &htim2);

}
void mission_3(){

	//竹簍
	//servo_right.update_pos(angle_2, 5);
	//servo_right.run();
	servo_left.update_pos(angle_2, 1);
	servo_left.run();

	//servo_right.update_pos(angle, 5);
	//servo_right.run();
	servo_left.update_pos(angle, 1);
	servo_left.run();

	
    
    // 第一次執行時初始化
    if (!initialized) {
        Motor_updown.mark_start_position();  // 記錄起始位置
        initialized = true;
        total_steps = 0;
    }

    // 執行馬達控制
    Motor_updown.PI_run();
    Motor_updown.setspeed(speeds);
    Motor_updown.update_speed(1);  // 更新encoder計數
    
    // 取得走了多少步
    int32_t steps = Motor_updown.get_steps_from_start();
    total_steps = abs(steps);  // 更新總步數
    
    // 顯示目前步數
    high = (float)total_steps;  // 使用high變數來顯示步數
    
    // 當碰到限位開關時，記錄最終步數並停止
    /*if (gripperHighest || gripperLowest) {
        speeds = 0;
    }*/
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
