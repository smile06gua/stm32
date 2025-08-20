/*
 * mainpp.h
 *
 *  Created on: Jul 8, 2025
 *      Author: USER
 */

#ifndef INC_MAINPP_H_
#define INC_MAINPP_H_

#ifdef __cplusplus
extern "C" {
#endif

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;

void main_function();

#ifdef __cplusplus
}
#endif

// C++ functions (outside extern "C" block)
void wait(int time, TIM_HandleTypeDef* htim);

#endif /* INC_MAINPP_H_ */
