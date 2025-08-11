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
private:
    float currentPos;
    float goalPos;
    float lastPos;
    int responseTime;
    bool move;
    int updateFreqency;
    TIM_HandleTypeDef *servo_htim;
    uint32_t servo_TIM_CHANNEL;

#endif /* INC_SERVO_H_ */
