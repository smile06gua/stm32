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
bool _basketFinish = 0;
bool _forwardFinish = 0;
float angle_per_mm = 880/294.55;
int zeroPointAngle = 440;
void mission_1(){

}

void mission_2(){
	//前後
    servo_forward.turnTo(30); //算座標
	wait(2000, &htim2);
	servo_forward.turnTo(910); //算座標
	wait(2000, &htim2);

	// 夾咖啡杯
	/*servo_gripper*/
	servo_gripper.turnTo(0);  //off
	wait(2000, &htim2);
	servo_gripper.turnTo(300);  //open
	wait(2000, &htim2);


}
void mission_3(){

	//竹簍
	//servo_right.update_pos(angle_2, 5);
	//servo_right.turnTo(angle);  // 0~55
	//servo_left.turnTo(angle_2);
	servo_gripper.turnTo(angle);
	Motor_updown.heightTo(high1);
	//wait(1000, &htim2);
	//servo_right.update_pos(angle, 5);
	//servo_right.turnTo(angle);
	//servo_left.turnTo(angle_2);




    // Motor_updown.PI_run();
    // 更新encoder計數

}
void mission_4(){

}

void gripperControl(bool open){
	if(open){
		servo_gripper.turnTo(300);  //open
		_gripperFinish = 1; //
	}
	else{
		servo_gripper.turnTo(0); //off
		_gripperFinish = 0;
	}
}

void basketControl(bool open){
	if(open){
		servo_left.turnTo(0);
		servo_right.turnTo(0);
		_basketFinish = 1;
	}
	else{
		servo_left.turnTo(0);
		servo_right.turnTo(0);
		_basketFinish = 0;
	}
}

void forwardControl(bool done){
	if(done){
		servo_forward.turnTo(90);  //open
		_forwardFinish = 1; //
	}
	else{
		servo_forward.turnTo(90); //off
		_forwardFinish = 0;
	}
}

void elevatorControl(float high){
	Motor_updown.heightTo(high);
}

void forwardToPoint(float forward_cm){
	if(forward_cm < 0){
		servo_forward.turnTo(int(zeroPointAngle + forward_cm*angle_per_mm));
	}
	else if(forward_cm > 0){
		servo_forward.turnTo(int(zeroPointAngle + forward_cm*angle_per_mm));
	}
	else{
		servo_forward.turnTo(zeroPointAngle);
	}
}

