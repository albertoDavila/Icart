# Icart

# Setup
## Prerequisites
The following steps are tested on Ubunto Bionic (18.04) and ROS Melodic. If you use different systems and come across weird error messages, consider upgrading to these.
You should have set up a catkin workspace (~/catkin_ws) and installed gazebo and gazebo for ROS.
If you didn't set up the catkin_workspace, do the following:
```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/
catkin_make
```

## Setting up the workspace
We need to set up the catkin workspace with our repository as well as other repos that we depend on:
```
cd ~/catkin_ws/src
git clone git@github.com:albertoDavila/Icart.git

cd ..
catkin_make
source devel/setup.bash

sudo apt-get install ros-melodic-teleop-twist-keyboard ros-melodic-gmapping ros-melodic-ros-control ros-melodic-move-base ros-melodic-effort-controllers ros-melodic-joint-state-controller ros-melodic-joint-state-publisher ros-melodic-robot-state-publisher ros-melodic-realsense2-camera ros-melodic-realsense2-description ros-melodic-moveit ros-melodic-moveit-visual-tools ros-melodic-gazebo-ros-pkgs ros-melodic-gazebo-ros-control ros-melodic-ros-controllers ros-melodic-map-server ros-melodic-gmapping
```

## Setting up the gazebo environment
In order to be able to open the .world files with the relative paths, you need to add the path to this repository. 
Run `vim ~/.bashrc`(or any other editor). At the bottom, insert a line 
`export GAZEBO_MODEL_PATH=(path to the git repository)`

For example, if the git repo (lab_automation folder) is at /catkin_ws/src/lab_automation (which it should be, if you followed the instructions), the line should be
`export GAZEBO_MODEL_PATH=/catkin_ws/src/` (dont forget the slash at the end). Afterwards, make sure to source the file (`source ~/.bashrc`).

Rviz should open the lab and the robot and after a while, the robot should start planning and executing the trajectory.



## Testing robotino navigation planning 

We need to launch the amcl_demo file, which contains the saved map, the amcl and move_base packages implemented: 
`roslaunch lab_automation amcl_demo.launch`

This file will open Gazebo and Rviz with the slam configuration 

Now, there are two options to perform the navigation: 

The first one is to use the "2D nav goal" in rviz and select the desired goal in the map. 

The other way is to use the cpp file go_to_position by using the command:
`rosrun lab_automation go_to_position` 

You have to change the values of goal.target_pose.pose.position.x, ,goal.target_pose.pose.position.y and goal.target_pose.pose.orientation.w depending on which goal point you want to reach. 

## Creating a New Map 

If you want to map a new environment you can use the gmapping_demo.lauch file. You just have to replace the gazebo world file (lab.world) with your file world you want to do the mapping. 

`roslaunch lab_automation gmapping_demo.lauch`

Then, you can use the keyboards and start to mapping your environment. After you have mapped the whole environment you need to save the map, this is done using the following command:

`rosrun map_server map_saver -f "your_file_name"`

Note that this command save two files (a your_file_name.pgm and your_file_name.yaml file) in the current directory of your command line.  We recommend you two save these files inside the Rviz folder (lab_automation/src/rviz). 


Now, you need to add a the .yaml file to your launch file. For example you can do add it to the amcl_demo.launch by replacing map_lab.yaml with your .yaml file in the following part of the code (if you  did not save your .yaml file inside the rviz folder, you also need to update the args)

```
<!-- Run the map server  -->
<node name="map_server" pkg="map_server" type="map_server" args="$(find lab_automation)/rviz/map_lab.yaml"/> 

```


```
