/*
 * servo.cpp
 *
 *  Created on: Jul 16, 2025
 *      Author: USER
 */

#include "stm32g4xx_hal.h"
#include "servo.h"

void Servo::setup(int startAngle){
	HAL_TIM_PWM_Start(htim, channel);
	write(startAngle);
}

void Servo::attach(uint32_t ch) {
	channel = ch;
}

void Servo::setTimer(TIM_HandleTypeDef* h) {
	htim = h;
}

void Servo::setMaxAngle(int ang){
	maxAng = ang;
}

void Servo::setPulseRange(int min,int max){
	maxPulse = max;
	minPulse = min;
}

void Servo::write(int ang) {
	
	angle = ang;
	int pulseRange = maxPulse - minPulse;
	float pulse = minPulse + (float)pulseRange * (float)ang / (float)maxAng;
	if(pulse > maxPulse)pulse = maxPulse;
	else if(pulse < minPulse)pulse = minPulse;
//	p = pulse;
	__HAL_TIM_SET_COMPARE(htim, channel, int(pulse));



}


void Servo::detach() {
	HAL_TIM_PWM_Stop(htim, channel);
}

