/*
 * servo.h
 *
 *  Created on: Jul 16, 2025
 *      Author: USER
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32G4xx_hal.h"

#include <cmath>


//int p = 0;
struct Info{
	int maxAng;
	int minPulse;
	int maxPulse;
	float maxServoSpeed;//rpm sec/60˚
};

//int p = 0;
class Servo {
	public:

		enum type{
			GBD300T,
			GBD300S,
			GBD1800T,
			GBD1800S
		};

	private:
		uint32_t channel;
		int angle;
		TIM_HandleTypeDef* htim;

		Info servoInfo = {300,500,2500,0.25};

		enum type ServoType = GBD300T;

		bool isMoving = false;


		static Info getServoInfo(type servoType){
			switch(servoType){
			case GBD300T:
				return {300,500,2500,0.25};
			case GBD300S:
				return {300,500,2500,0.11};
			case GBD1800T:
				return {1800,500,2500,0.25};
			case GBD1800S:
				return {1800,500,2500,0.11};
			default:
				return getServoInfo(GBD300T);
			}
		}


	public:

		Servo(TIM_HandleTypeDef* h, uint32_t ch,int MaxAngle = 300,int MinPulse = 500,int MaxPulse = 2500,int maxServoSpeed = 0.25) {
			htim = h;
			channel = ch;
			servoInfo.maxAng = MaxAngle;
			servoInfo.minPulse = MinPulse;
			servoInfo.maxPulse = MaxPulse;
			servoInfo.maxServoSpeed = maxServoSpeed;
		}

		Servo(TIM_HandleTypeDef* h, uint32_t ch,type servoType) {
			htim = h;
			channel = ch;
			servoInfo = getServoInfo(servoType);
		}
		void setMaxServoSpeed(float rpm);
		void setup(int startAngle = 0);
		void attach(uint32_t ch);
		void setTimer(TIM_HandleTypeDef* h);
		void setMaxAngle(int ang);
		void setPulseRange(int min,int max);
		void write(int ang);//直接轉到對的位置
		void turnTo(int ang,int interval = 0);//會檢查有沒有轉到 interval單位是ms
		void detach();
};
#endif /* INC_SERVO_H_ */
