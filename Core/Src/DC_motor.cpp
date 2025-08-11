/*
 * DC_motor.cpp
 *
 *  Created on: Jul 8, 2025
 *      Author: USER
 */

#include "DC_motor.h"
#include "stm32g4xx_hal.h"
#include <cstdlib>
#include <cmath>

float uuuuuu = 0;

void DC_motor::PI_run() {
    float p, i, d;
    float max_integral = 100.0f;
    error = sp - speed;

    // 不禁止 error，只禁止積分
    if (fabsf(error) < 0.f) {
        // 小誤差不累積積分
    } else {
        integral += error;
    }

    if (integral > max_integral) integral = max_integral;
    else if (integral < -max_integral) integral = -max_integral;

    differential = error - pre_error;
    pre_error = error;

    p = kp * error;
    i = ki * integral;
    d = kd * differential;

    float u = p + i + d;
    uuuuuu = u;

    if (u > 1.0f) u = 1.0f;
    else if (u < -1.0f) u = -1.0f;

    pulse = fabsf(u) * arr;

    if (u > 0) {
        HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_SET);
    }

    __HAL_TIM_SET_COMPARE(PWM_htim, PWM_TIM_CHANNEL, (uint16_t)pulse);
}


void DC_motor::setspeed(float target_speed){
    sp = target_speed;
}
void DC_motor::update_speed(int sign){
    int16_t enc ;
	enc = __HAL_TIM_GetCounter(enc_htim);
	speed = sign*(float)enc /(4*resolution*span*reduction_ratio);
    __HAL_TIM_SetCounter(enc_htim,0);
}
void DC_motor::setup(){
    HAL_TIM_PWM_Start_IT(PWM_htim, PWM_TIM_CHANNEL);
    HAL_TIM_Encoder_Start(enc_htim, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(enc_htim, TIM_CHANNEL_2);
}


