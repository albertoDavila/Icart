#include "ros/ros.h"
#include "std_msgs/String.h"
#include <moveit/move_group_interface/move_group_interface.h>
#include <lab_automation/PoseGoal.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Quaternion.h>
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/CollisionObject.h>
#include <sstream>
#include <geometric_shapes/shapes.h>
#include <geometric_shapes/shape_messages.h>
#include <geometric_shapes/shape_operations.h>
#include <geometric_shapes/mesh_operations.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Quaternion.h>
int main(int argc, char **argv)
{
    // set up poses_publisher node for publishing the poses where to pick and place an object
    ros::init(argc, argv, "put_centrifuge");
    ros::NodeHandle n;
    ros::Publisher pose_goal_publisher = n.advertise<lab_automation::PoseGoal>("/ns/pose_goal", 10);
    ros::Duration(1).sleep();

    ROS_INFO("Starting the put centrifuge pose publisher...");

    // Set the tubule position
    geometry_msgs::Pose tubule_pose;
    tf2::Quaternion rotation;
    rotation.setRPY(1.57, 0, 0);
    tubule_pose.orientation = tf2::toMsg(rotation);
   tubule_pose.position.x = 0.38;
    tubule_pose.position.y = -0.11;
    tubule_pose.position.z = 0.8; 

    // Publish the environment (tubule position)
    lab_automation::PoseGoal pose_goal_msg;
    moveit_msgs::CollisionObject collision_object;

    // Add the tubule to collision objects.
    collision_object.id = "tubule";
    collision_object.header.frame_id = "base_link";
    collision_object.operation = collision_object.ADD;
    const Eigen::Vector3d scaling(.002, .002, .002);
    shapes::Mesh *m = shapes::createMeshFromResource("package://lab_automation/worlds/models/tubule2.stl", scaling);
    shape_msgs::Mesh tubule_mesh;
    shapes::ShapeMsg tubule_mesh_msg;
    shapes::constructMsgFromShape(m, tubule_mesh_msg);
    tubule_mesh = boost::get<shape_msgs::Mesh>(tubule_mesh_msg);
    collision_object.meshes.push_back(tubule_mesh);
    collision_object.mesh_poses.push_back(tubule_pose);
    ROS_INFO("ID of collision object:");
    std::cout<<collision_object.id<<std::endl;

    pose_goal_msg.collision_objects.push_back(collision_object);

    // define pose for picking an object
     geometry_msgs::Pose pose_goal;
    pose_goal.orientation.x = 0;
    pose_goal.orientation.y = 1;
    pose_goal.orientation.z = 0;
    pose_goal.orientation.w = 0;
    pose_goal.position = tubule_pose.position;
    pose_goal.position.x = -0.67;
    pose_goal.position.y = 0.45;
    pose_goal.position.z = 0.46;
    pose_goal_msg.pose_goal = pose_goal;

    // Whether we want to pick the tubule or place it
    pose_goal_msg.pick_tubule.data = true;

    //Whether we want to grab the tubule from the side or from top
    pose_goal_msg.grab_from_top.data = false;

    ROS_INFO("Put Centrifuge: Sending pose goal message.");

    // Publish the message
    pose_goal_publisher.publish(pose_goal_msg);

    ros::spin();

    return 0;
}
