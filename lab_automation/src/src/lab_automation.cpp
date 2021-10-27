#include "ros/ros.h"
#include <sstream>
#include "ros/ros.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "lab_automation");
    ros::NodeHandle n;
    ROS_INFO("Starting the lab automation script...Initializing");

    // TODO drive robotino to fume hood
    
    
    // TODO drive robotino from fume hood to centrifuge

    // TODO drive robotino from centrifuge to water bath

    // TODO drive robotino from water bath to original position

    ros::spin();

    return 0;
}
