/*
 * ros1.h
 *
 *  Created on: Aug 6, 2024
 *      Author: pomelo925
 */

#ifndef ROS_1_H_
#define ROS_1_H_

#include "geometry_msgs/Twist.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float64.h"

extern float speeds;
extern bool table_isTouch;
extern bool isTop;
extern int elevator_type;
extern bool gripperIsGet;
extern bool basketIsGet;
extern bool _gripperFinish;
extern bool _basketFinish;
extern bool _Finish;
extern float _current_y;
extern float _current_theta;

namespace ROS1 {
	void init(void);
	void spinCycle(void);

	void _pub_gripper(void);
	void _pub_basket(void);
	void _pub_elevator(void);
	void _pub_touch(void);
	void _pub_y(void);
	void _pub_theta(void);


	void callback_gripper(const std_msgs::Bool &msg);
	void callback_Elevator(const std_msgs::Int32 &msg);
	void callback_turn(const std_msgs::Int32 &msg);
	void callback_forward(const std_msgs::Int32 &msg);
	void callback_BasketDoor(const std_msgs::Bool &msg);
}


#endif
