/*
 * DC_motor.h
 *
 *  Created on: Jul 8, 2025
 *      Author: USER
 */

#ifndef INC_DC_MOTOR_H_
#define INC_DC_MOTOR_H_


#include "stm32g4xx_hal.h"

class DC_motor{
public:
	void setup();
	void PI_run();
	void update_speed(int sign);
	float get_speed() const { return speed; }
	void setspeed(float target_speed);


	DC_motor(TIM_HandleTypeDef *_enc_htim, GPIO_TypeDef *_dirPort, uint16_t _dirPin, TIM_HandleTypeDef *_PWM_htim, uint32_t _PWM_TIM_CHANNEL) {
		enc_htim = _enc_htim;
		dirPort = _dirPort;
		dirPin = _dirPin;
		PWM_htim = _PWM_htim;
		PWM_TIM_CHANNEL = _PWM_TIM_CHANNEL;
	};
private:
	//PID parameter
	float kp = .21 ,ki = 0.0005,kd = 0.f;
	//error
	float error = 0.f,pre_error = 0.f,integral = 0.f,differential = 0.f;
	//sp of velocity
	float speed = 0.f;
	float sp = 0.f;
	//motor and encoder information
	float span = 0.001;
	int resolution = 256;
	float reduction_ratio = 24;
	int dir = 0;
	int arr = 999;
	int pulse = 0;
	TIM_HandleTypeDef *enc_htim;
	//motor driver
	GPIO_TypeDef *dirPort;
	uint16_t dirPin;
	TIM_HandleTypeDef *PWM_htim;
	uint32_t PWM_TIM_CHANNEL;

};



#endif /* INC_DC_MOTOR_H_ */
