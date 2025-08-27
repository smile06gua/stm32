/*
 * servo.cpp
 *
 *  Created on: Jul 16, 2025
 *      Author: USER
 */

#include "stm32g4xx_hal.h"
#include "servo.h"
#include "mainpp.h"

float minInterval = 0;
int t = 0;

void Servo::setMaxServoSpeed(float rpm){
	servoInfo.maxServoSpeed = rpm;
}

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
	servoInfo.maxAng = ang;
}

void Servo::setPulseRange(int min,int max){
	servoInfo.maxPulse = max;
	servoInfo.minPulse = min;
}

void Servo::write(int ang) {
	angle = ang;
	int pulseRange = servoInfo.maxPulse - servoInfo.minPulse;
	float pulse = servoInfo.minPulse + (float)pulseRange * (float)ang / (float)servoInfo.maxAng;
	if(pulse > servoInfo.maxPulse)pulse = servoInfo.maxPulse;
	else if(pulse < servoInfo.minPulse)pulse = servoInfo.minPulse;
//	p = pulse;
	__HAL_TIM_SET_COMPARE(htim, channel, int(pulse));
}


void Servo::detach() {
	HAL_TIM_PWM_Stop(htim, channel);
}


void Servo::turnTo(int ang,int interval){
	if(ang > servoInfo.maxAng)return;
	if(ang < 0)return;
	const float deltaDeg = ang - angle;
	minInterval = abs(deltaDeg)*servoInfo.maxServoSpeed/60.0*1000.0;
	minInterval *= 1.1;
	if(interval <  minInterval){
		interval = minInterval;
		write(ang);
		wait(interval,&htim2);
		return;
	}
	const int dt_ms = 10;
	const int lastAng = angle;
	t = 0;
	while(1){
		if (t > interval-dt_ms) break;
		float u = (float)t / (float)interval;    // 0~1
		int a = lastAng + deltaDeg * u;
		write(a);
		wait(dt_ms,&htim2);
		t += dt_ms;
	}
	write(ang);
}


