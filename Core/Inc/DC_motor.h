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

    // 設定高度校正值（輸入總高度差和對應的encoder數）
    void calibrate_height(float total_height_mm, int32_t total_steps);

    // 取得目前高度（mm）
    float get_current_height() const;
    
    // 記錄起始位置的encoder count
    void mark_start_position();
    
    // 取得從起始位置走了多少步
    int32_t get_steps_from_start() const;

	DC_motor(TIM_HandleTypeDef *_enc_htim, GPIO_TypeDef *_dirPort, uint16_t _dirPin, TIM_HandleTypeDef *_PWM_htim, uint32_t _PWM_TIM_CHANNEL) {
		enc_htim = _enc_htim;
		dirPort = _dirPort;
		dirPin = _dirPin;
		PWM_htim = _PWM_htim;
		PWM_TIM_CHANNEL = _PWM_TIM_CHANNEL;
		total_encoder_count = 0;
        mm_per_step = 0;  // 初始化每步對應的高度
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
	int resolution = 100;
	float reduction_ratio = 64;
	int dir = 0;
	int arr = 999;
	int pulse = 0;
	TIM_HandleTypeDef *enc_htim;
	//motor driver
	GPIO_TypeDef *dirPort;
	uint16_t dirPin;
	TIM_HandleTypeDef *PWM_htim;
	uint32_t PWM_TIM_CHANNEL;
	int32_t total_encoder_count = 0;
    float mm_per_step = 0;  // 每個encoder步數對應的高度(mm)
    int32_t start_position = 0;  // 記錄起始位置的encoder count
};



#endif /* INC_DC_MOTOR_H_ */
