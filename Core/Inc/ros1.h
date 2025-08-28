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

extern bool gripperIsGet;
extern bool basketIsGet;
extern bool _gripperFinish;
extern bool _basketFinish;
extern bool _Finish;

namespace ROS1 {
	void init(void);
	void spinCycle(void);

	void _pub_gripper(void);
	void pub_basketFinish(void);
	void pub_elevatorHeight(void);


	void callback_gripper(const std_msgs::Bool &msg);
	void callback_Elevator(const std_msgs::Float64 &msg);
	void callback_BasketDoor(const std_msgs::Bool &msg);
}


#endif
