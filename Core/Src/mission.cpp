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

bool _gripperFinish = 0;

void mission_1(){

}

void mission_2(){
	//前後
    servo_forward.write(90); //算座標
	wait(5000, &htim2);
	servo_forward.write(950); //算座標
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




    Motor_updown.PI_run();
      // 更新encoder計數

}
void mission_4(){

}

void gripperControl(bool open){
	if(open){
		servo_gripper.write(300);  //open
		_gripperFinish = 1; //
	}
	else{
		servo_gripper.write(0); //off
		_gripperFinish = 0;
	}
}

void basketControl(bool open){
	if(open){
		servo_left.write(0);
		servo_right.write(0);
	}
	else{
		servo_left.write(0);
		servo_right.write(0);
	}
}


