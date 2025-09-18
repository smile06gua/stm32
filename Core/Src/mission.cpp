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
bool _forwardFinish = 0; // ???


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
	//servo_gripper.turnTo(angle);
	if(initialized){
		Motor_updown.heightTo(high1);
	}

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
	if(open == 0){
		servo_gripper.turnTo(900, 1500);  //close
		_gripperFinish = 0; //
	}
	else{
		servo_gripper.turnTo(470, 1500); //open
		_gripperFinish = 1;
	}
}

void middleTurn(int angle){
	float degree = angle;
	_current_theta = angle;
	if(angle < 0 && angle > -260){
		servo_turn.turnTo(261.0 + degree, 5000);
	}
	if(angle >= 0 && angle < 30){
		servo_turn.turnTo(261.0 + degree, 5000);
	}
}

void basketControl(bool open){
	if(open){
		servo_left.turnTo(50);
		servo_right.turnTo(5);
		_basketFinish = 1;
	}
	else{
		servo_left.turnTo(0);
		servo_right.turnTo(58);
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

void for_last_mission(){
	servo_turn.turnTo(81);
	servo_forward.turnTo(30);
}

void forwardToPoint(float forward_mm){
	if(forward_mm < 0 && forward_mm > -90){
		servo_forward.turnTo(int(zeroPointAngle + forward_mm*angle_per_mm));
		_current_y = forward_mm;
		
	}
	else if(forward_mm > 0 && forward_mm < 220){
		servo_forward.turnTo(int(zeroPointAngle + forward_mm*angle_per_mm));
		_current_y = forward_mm;
	}
	else if(forward_mm == 0){
		servo_forward.turnTo(zeroPointAngle);
		_current_y = 0;
	}
}

