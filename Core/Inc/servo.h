/*
 * servo.h
 *
 *  Created on: Jul 16, 2025
 *      Author: USER
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32g4xx_hal.h"

class servo{
public:
    void setup();
    void update_pos(float goalpos,int responseTime);
    void run();

    servo(TIM_HandleTypeDef *_servo_htim, uint32_t _servo_TIM_CHANNEL){
    	servo_htim = _servo_htim;
    	servo_TIM_CHANNEL = _servo_TIM_CHANNEL;
    	updateFreqency = 1000;
    };

private:
    float currentPos = 0;
    float goalPos = 0;
    float lastPos = 0;
    float maxAngle = 300;
    int maxPulse = 2500;
    int minPulse = 500;
    int responseTime = 0;
    bool move = 0;
    int updateFreqency = 0;
    TIM_HandleTypeDef *servo_htim;
    uint32_t servo_TIM_CHANNEL;
};
#endif /* INC_SERVO_H_ */
