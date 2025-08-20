/*
 * mission.cpp
 *
 *  Created on: Aug 14, 2025
 *      Author: USER
 */

#include "mission.h"
#include "servo.h"
#include "mainpp.h"
#include <cmath>


void mission_1(){

}

void mission_2(){
    servo_forward.write(90);
	wait(5000, &htim2);
	servo_forward.write(950);
	wait(5000, &htim2);

	// 夾咖啡杯
	/*servo_gripper*/
	servo_gripper.write(0);  //off
	wait(2000, &htim2);
	servo_gripper.write(300);  //open
	wait(2000, &htim2);
}
void mission_3(){

	//竹簍
	//servo_right.update_pos(angle_2, 5);
	//servo_right.run();
	servo_left.write(0);


	//servo_right.update_pos(angle, 5);
	//servo_right.run();
	servo_left.write(0);




    // 第一次執行時初始化
    if (!initialized) {
        Motor_updown.mark_start_position();  // 記錄起始位置
        initialized = true;
        total_steps = 0;
    }

    // 執行馬達控制
    Motor_updown.PI_run();
    Motor_updown.setspeed(speeds);
    Motor_updown.update_speed(1);  // 更新encoder計數

    // 取得走了多少步
    int32_t steps = Motor_updown.get_steps_from_start();
    total_steps = abs(steps);  // 更新總步數

    // 顯示目前步數
    high = (float)total_steps;  // 使用high變數來顯示步數

    // 當碰到限位開關時，記錄最終步數並停止
    /*if (gripperHighest || gripperLowest) {
        speeds = 0;
    }*/
}


