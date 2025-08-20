/*
 * mission.h
 *
 *  Created on: Aug 14, 2025
 *      Author: USER
 */

#ifndef INC_MISSION_H_
#define INC_MISSION_H_

#include "stm32g4xx_hal.h"
#include "DC_motor.h"
#include "servo.h"

// 宣告外部變數，這些是在mainpp.cpp中定義的實例
extern bool initialized;
extern float speeds;
extern float range;
extern float add;
extern float angle;
extern float angle_2;
extern float high;
extern int delay_count;
extern int gripperHighest;
extern int gripperLowest;
extern int32_t total_steps;
extern DC_motor Motor_updown;
extern Servo servo_forward;
extern Servo servo_gripper;
extern Servo servo_trun;
extern Servo servo_left;
extern Servo servo_right;   

void mission_1();
void mission_2();
void mission_3();
void mission_4();


#endif /* INC_MISSION_H_ */
