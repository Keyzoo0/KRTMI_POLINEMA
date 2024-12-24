cmake_minimum_required(VERSION 3.0.2)
project(rotema)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)
catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(forwardNode src/forward.cpp)

## Hubungkan eksekutabel dengan library ROS
target_link_libraries(forwardNode
  ${catkin_LIBRARIES}
)
