/*
 * servo.cpp
 *
 *  Created on: Jul 16, 2025
 *      Author: USER
 */

#include "servo.h"
#include "stm32g4xx_hal.h"

void servo::setup(){
    HAL_TIM_PWM_Start(servo_htim, servo_TIM_CHANNEL);
}
void servo::update_pos(float _goalPos,int _responseTime){
    goalPos = _goalPos;
    responseTime = _responseTime;
    move = true;
}
void servo::run(){//updateFreq = timer interrupt frequency Hz
	if (move == true){
		if ((int) currentPos == (int) goalPos){
    	 move = false;
    	 lastPos =  goalPos;
        }else{
         float distance = goalPos -  lastPos;
          pos += distance/( responseTime * updateFreq / 1000);
         __HAL_TIM_SET_COMPARE(servo_htim, servo_TIM_CHANNEL,600+10*(int)pos);
         //t++;
        }
	}
}
