/*
 * DC_motor.cpp
 *
 *  Created on: Jul 8, 2025
 *      Author: USER
 */
// For int16_t
#include "DC_motor.h"
#include "stm32g4xx_hal.h"
#include <cstdlib>
#include <cmath>




void DC_motor::PI_run(){
    float u = 0;
    int pul = 0;
    float bound = 1/ki;
    error = sp - speed;
    integral += error*span;
    differential = error - pre_error;

    if (integral > bound)integral = bound;
    else if (integral < -bound)integral = -bound;
    u = kp*error + ki*integral + kd*differential;
    pre_error = error;

    if (u > 1) u = 1;
    else if (u < -1) u = -1;
    pul = (int)(fabs(u)*arr);
    if(dir_pin == true){
       	if(u>0){
       	        HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_RESET);
       	    }else if (u<0){
       	        HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_SET);
       	    }else{
       	        pul = 0;
       	    }
       }else if(dir_pin == false){
       	if(u>0){
       	        HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_SET);
       	    }else if (u<0){
       	        HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_RESET);
       	    }else{
       	        pul = 0;
       	    }
       }
    __HAL_TIM_SET_COMPARE(PWM_htim, PWM_TIM_CHANNEL, pul);
}


void DC_motor::setspeed(float target_speed){
    sp = target_speed;
}
void DC_motor::update_speed(int sign){
    int16_t enc ;
	enc = __HAL_TIM_GetCounter(enc_htim);
	speed = sign*(float)enc /(4*resolution*span*reduction_ratio);
	turn += speed*span;
    __HAL_TIM_SetCounter(enc_htim,0);
}
void DC_motor::setup(){
    HAL_TIM_PWM_Start_IT(PWM_htim, PWM_TIM_CHANNEL);
    HAL_TIM_Encoder_Start(enc_htim, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(enc_htim, TIM_CHANNEL_2);
}
void DC_motor::set_motor_parameter(float reduction_ratio,int resolution) {
    this->reduction_ratio = reduction_ratio;
    this->resolution = resolution;
}

// 控cascade lift

void DC_motor::heightTo(float high){
	//height = 25 + turn * mm_per_turn;
	//target_turns = 0.0f;
	if(high != 0){
		if(high >= height){
			target_turns = turn + ( (high - height )/ mm_per_turn );
		}
		else{
			target_turns = turn - ( (height - high ) / mm_per_turn );
		}

		while(turn < target_turns && high1 != 0){
			if(fabs(target_turns - turn) < 0.001){
				//target_turns = 0;
				high1 = 0;
				setspeed(0);
				break;
			}
			else{
				setspeed(0.1);
			}
		}
		while(turn > target_turns && high1 != 0){
			if(fabs(target_turns - turn) < 0.001){
				//target_turns = 0;
				high1 = 0;
				setspeed(0);
				break;
			}
			else{
				setspeed(-0.1);
			}

		}
	}

	//setspeed(0);
}
