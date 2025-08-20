/*
 * servo.h
 *
 *  Created on: Jul 16, 2025
 *      Author: USER
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32G4xx_hal.h"

namespace Jason{

//int p = 0;
class Servo {
	private:
		uint32_t channel;
		int angle;
		TIM_HandleTypeDef* htim;
		int maxAng = 300;
		int maxPulse = 2500;
		int minPulse = 500;


	public:
		Servo(TIM_HandleTypeDef* h, uint32_t ch) {
			htim = h;
			channel = ch;
		}
		void setup(int startAngle = 0);
		void attach(uint32_t ch);
		void setTimer(TIM_HandleTypeDef* h);
		void setMaxAngle(int ang);
		void setPulseRange(int min,int max);
		void write(int ang);
		void detach();
};

}
#endif /* INC_SERVO_H_ */
