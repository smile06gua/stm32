/*
 * encoder.cpp
 *
 *  Created on: Jul 8, 2025
 *      Author: USER
 */


#include "encoder.h"
#include "stm32g4xx_hal.h"
/*
float wheel_dia_mm = 5.0f; // 轮径，单位mm
float wheel_circumference_mm = wheel_dia_mm * 3.14159265358979323846f; // 轮周长
//float wheel_circumference_m = wheel_circumference_mm / 1000.0f; // 轮周长，单位m 
int ppr = 100; // 每圈脉冲数
int gear_ratio = 64; // 齿轮减速比
float meters_per_tick = wheel_circumference_mm / (ppr * gear_ratio * 1000.0f); // 每个脉冲对应的距离，单位m
float wheel_speed_mps = 0.0f; // 轮速，单位m/s	
*/
void encoder::init(){
	HAL_TIM_Encoder_Start(enc_htim, TIM_CHANNEL_ALL);
}
void encoder::update_speed(int sign){
	int16_t enc ;
	enc = __HAL_TIM_GetCounter(enc_htim);
	speed = sign*(float)enc /(4*resolution*span);
}

/*
int16_t enc;
float speed;
float resolution = 256;       // 例如：每圈脈波數
float reduction_ratio = 1.0;     // 例如：減速比
float span = 0.001;
int count = 0;

DC_motor wheel_1 ={&htim4,GPIOA,GPIO_PIN_10,&htim8,TIM_CHANNEL_1};

void setup(){
	wheel_1.setup();
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);
}

void run_dir(){

	wheel_1.setspeed(10.0f);
	wheel_1.PI_run();
	HAL_Delay(5000);// 設定目標正轉速度

	// 反轉
	wheel_1.setspeed(-10.0f);      // 設定目標反轉速度
	wheel_1.PI_run();
	HAL_Delay(5000);// 設定目標正轉速度

	// 停止
	wheel_1.setspeed(0.0f);
	wheel_1.PI_run();
	HAL_Delay(1000);

}
*/


