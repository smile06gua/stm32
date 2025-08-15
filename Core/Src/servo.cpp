/*
 * servo.cpp
 *
 *  Created on: Jul 16, 2025
 *      Author: USER
 */

#include "servo.h"
#include "stm32g4xx_hal.h"
int pulse = 0;
int pos = 0;
float distance = 0;

void servo::setup(){
    HAL_TIM_PWM_Start(servo_htim, servo_TIM_CHANNEL);
}
void servo::update_pos(float _goalPos,int _responseTime){
    goalPos = _goalPos;
    responseTime = _responseTime;
    move = true;
    //run();
}

void servo::run(){//updateFreq = timer interrupt frequency Hz
	//可控夾爪，其他超怪
    if (move == true){
		if (((currentPos >= goalPos && goalPos >= lastPos) || (currentPos <= goalPos && goalPos<=lastPos))){
    	 move = false;
    	 lastPos =  goalPos;
    	 pos = goalPos;
        }else{
         distance = goalPos -  lastPos;
         pos += distance/( responseTime * updateFreqency / 1000);
         pulse = pos / maxAngle * ( maxPulse - minPulse );
         __HAL_TIM_SET_COMPARE(servo_htim, servo_TIM_CHANNEL, minPulse + pulse);
         currentPos = pos;
//         run();
         //t++;
        }

	}
    /*
   for(pos = 0; pos <= goalPos; pos++){
    __HAL_TIM_SET_COMPARE(servo_htim, servo_TIM_CHANNEL, minPulse + pos / maxAngle * (maxPulse - minPulse));
    HAL_Delay(100);
   }

   for(pos = goalPos; pos > 0; pos--){
    __HAL_TIM_SET_COMPARE(servo_htim, servo_TIM_CHANNEL, minPulse + pos / maxAngle * (maxPulse - minPulse));
    HAL_Delay(100);
   }
   */

}
