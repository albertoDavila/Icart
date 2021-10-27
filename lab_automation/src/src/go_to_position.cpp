#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

//Replace the main with the next line if you want to send publish a message if the robotino reach the goal (see drive_centrifuge.cpp in the branch "merge-scripts-2")
//int driveToCentrifuge(ros::Publisher execution_completed_publisher){

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move toward the goal
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = -3.32;
  goal.target_pose.pose.position.y = 3.27;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

// use it if you want to publish a bool message instead of display a ros_info
//if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//   execution_completed_publisher.publish(true);

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Goal achieved");
  else
    ROS_INFO("The base failed to move for some reason");

  return 0;
}
