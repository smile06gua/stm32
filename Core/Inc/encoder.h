/*
 * encoder.h
 *
 *  Created on: Jul 8, 2025
 *      Author: USER
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32g4xx_hal.h"

class encoder{
public:
	void update_speed(int);
	void init();
private:
	int resolution;
	float span;
	TIM_HandleTypeDef *enc_htim;
	float speed;
};

#endif /* INC_ENCODER_H_ */
