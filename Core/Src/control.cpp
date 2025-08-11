/*
 * control.cpp
 *
 *  Created on: Jul 8, 2025
 *      Author: USER
 */

#include "control.h"
#include "DC_motor.h"
#include "stm32g4xx_hal.h"

/*
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;

int16_t enc = 0;                 // 編碼器讀值
float speed = 0.0;              // 計算出的實際轉速 (rad/s 或 m/s)
uint32_t time_div = 0;           // 中斷次數計數器
uint32_t time_s = 0;             // 秒數計數器（每 freq 次中斷加一秒）

float resolution = 256;       // 例如：每圈脈波數
float reduction_ratio = 1.0;     // 例如：減速比
float span = 0.001;

float sp = 10.0;                // 設定的目標轉速（可用 setter 設定）
float error = 0.0;              // e(t) = sp - speed
float integral = 0.0;           // 積分項 I(t)
float bound = 0.0;              // 積分限制用界限（= 1/ki）
float u = 0.0; 				 // 控制輸出（-1.0 ~ 1.0）

float kp = 0.3f;                 // 比例增益
float ki = 5.0f;                 // 積分增益

int pulse = 0;                   // PWM 實際輸出（對應 CCR）
uint32_t freq = 100;             // 中斷頻率（每秒呼叫幾次 callback，用來控制 time_s）




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM2){ // 確認中斷來源

		wheel_1.setspeed(sp);
		wheel_1.PI_run();

	}
}
*/

