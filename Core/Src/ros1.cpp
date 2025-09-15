/*
 * ros1.cpp
 *
 *  Created on: Aug 6, 2024
 *      Author: pomelo925
 */

#include "ros.h"
#include <ros1.h>
//#include <chassis.h>
#include "mission.h"
#include "DC_motor.h"
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
ros::NodeHandle nh;

/** STM Publishers **/
//geometry_msgs::Twist chassis_current_speed;
//ros::Publisher pub_chassis("/odometry", &chassis_current_speed);

std_msgs::Bool gripperFinish;
ros::Publisher pub_gripper("/gripper", &gripperFinish);
std_msgs::Bool touchFinish;
ros::Publisher pub_touch("/touch", &touchFinish);
std_msgs::Bool basketFinish;
ros::Publisher pub_basket("/basket", &basketFinish);
std_msgs::Float64 elevatorHeight;
ros::Publisher pub_elevator("/elevator", &elevatorHeight);
//send position x, theta
std_msgs::Float64 current_y;
std_msgs::Float64 current_theta;
ros::Publisher pub_y("/current_y", &current_y);
ros::Publisher pub_theta("/current_theta", &current_theta);

/** STM Subscribers **/
//ros::Subscriber<geometry_msgs::Twist> sub_chassis("/cmd_vel", ROS1::callback_Chassis);
ros::Subscriber<std_msgs::Bool> sub_gripper("/cmd_gripperOpen", ROS1::callback_gripper);
ros::Subscriber<std_msgs::Int32> sub_turn("/cmd_servoturn", ROS1::callback_turn);
ros::Subscriber<std_msgs::Int32> sub_forward("/cmd_forward", ROS1::callback_forward);
ros::Subscriber<std_msgs::Int32> sub_elevatorHeight("/cmd_elevator", ROS1::callback_Elevator);
ros::Subscriber<std_msgs::Bool> sub_basketDoor("/cmd_basketDoor", ROS1::callback_BasketDoor);


namespace ROS1 {
  /**
   * @brief ROS1 節點宣告。
   * @param void
   */
  void init(void){
    nh.initNode();

    nh.advertise(pub_gripper);
    nh.advertise(pub_basket);
    nh.advertise(pub_elevator);
    nh.advertise(pub_touch);
    nh.advertise(pub_y);
    nh.advertise(pub_theta);

    nh.subscribe(sub_gripper);
    nh.subscribe(sub_elevatorHeight);
    nh.subscribe(sub_basketDoor);
    nh.subscribe(sub_turn);
    nh.subscribe(sub_forward);

    return;
  }


  /**
   * @brief ROS1 循環單位。
   * @param void
   */
  void spinCycle(void){
    nh.spinOnce();
    return;
  }

  void _pub_touch(void){
	touchFinish.data = table_isTouch;
	pub_touch.publish(&touchFinish);
	return;
  }
  void _pub_gripper(void){
    gripperFinish.data = _gripperFinish;
    //	gripperIsGet = 0;
    pub_gripper.publish(&gripperFinish);
    return;
  }

  void _pub_basket(void){
    basketFinish.data = _basketFinish;
   // basketIsGet = 0;
    pub_basket.publish(&basketFinish);
    return;
  }
  void _pub_elevator(void){
    elevatorHeight.data = high;
    pub_basket.publish(&basketFinish);
    return;
  }
  void _pub_y(void){
    current_y.data = _current_y;
    pub_y.publish(&current_y);
    return;
  }
  void _pub_theta(void){
    current_theta.data = _current_theta;
    pub_theta.publish(&current_theta);
    return;
  }

  void callback_turn(const std_msgs::Int32 &msg){
	  if(isTop == 1){
		  middleTurn(msg.data);
	  }
	  else{
		  speeds = 0.5;
	  }
  }
  /**
   * @brief Intake 回調函數。
   * @param std_msgs::Bool
   */
  void callback_gripper(const std_msgs::Bool &msg){
	//gripperIsGet = 1;
	gripperControl(msg.data);
	// else runIntake = false;
	return;
  }

  void callback_basketDoor(const std_msgs::Bool &msg){
	basketControl(msg.data);
	return;
   }

  void callback_forward(const std_msgs::Int32 &msg){   //-90~220
	  forwardToPoint(msg.data);
	  return;
  }

  /**
   * @brief Elevator 回調函數。
   * @param std_msgs::Int32
   */
  void callback_Elevator(const std_msgs::Int32 &msg){
	  if(table_isTouch == 0){
		if(elevator_type  != -1 && msg.data == -1){
			speeds = -0.5;
		}
		else if(elevator_type  != 3 && msg.data == 1 && isTop == 0){
			speeds = 0.5;
		}
		      // runElevator = msg.data;
		 else{
			Motor_updown.heightTo((float) msg.data);
		 }
	  }


    return;
  }


  /**
   * @brief BasketDoor 回調函數。
   * @param std_msgs::Bool
   */
  void callback_BasketDoor(const std_msgs::Bool &msg){
    // if(msg.data) runBasketDoor = true;
    // else runBasketDoor = false;
    return;
  }
}
