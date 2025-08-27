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

ros::NodeHandle nh;

/** STM Publishers **/
//geometry_msgs::Twist chassis_current_speed;
//ros::Publisher pub_chassis("/odometry", &chassis_current_speed);

std_msgs::Bool gripperFinish;
ros::Publisher pub_gripper("/gripper", &gripperFinish);
std_msgs::Bool basketFinish;
ros::Publisher pub_basket("/basket", &basketFinish);
std_msgs::Int32 elevator;
ros::Publisher pub_elevator("/gripper", &elevator);

/** STM Subscribers **/
//ros::Subscriber<geometry_msgs::Twist> sub_chassis("/cmd_vel", ROS1::callback_Chassis);
ros::Subscriber<std_msgs::Bool> sub_gripper("/cmd_gripperOpen", ROS1::callback_gripper);
ros::Subscriber<std_msgs::Int32> sub_elevatorHigh("/cmd_elevator", ROS1::callback_Elevator);
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

    nh.subscribe(sub_gripper);
    nh.subscribe(sub_elevatorHigh);
    nh.subscribe(sub_basketDoor);

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


  void _pub_gripper(void){
    gripperFinish.data = _gripperFinish;
    gripperIsGet = 0;
    pub_gripper.publish(&gripperFinish);
    return;
  }

  void _pub_basket(void){
    basketFinish.data = _basketFinish;
    basketIsGet = 0;
    pub_basket.publish(&basketFinish);
    return;
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
	//basketIsGet = 1;
	gripperControl(msg.data);
	// else runIntake = false;
	return;
   }



  /**
   * @brief Elevator 回調函數。
   * @param std_msgs::Int32
   */
  void callback_Elevator(const std_msgs::Int32 &msg){
    // runElevator = msg.data;
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
