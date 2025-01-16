cmake_minimum_required(VERSION 3.0.2)
project(rotema)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  nav_msgs
  tf2
  tf2_ros
  geometry_msgs
)
catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(RobotNavigationNode src/RobotNavigation.cpp)
target_link_libraries(RobotNavigationNode
  ${catkin_LIBRARIES}
)


add_executable(RobotPositionNode src/RobotPosition.cpp)
target_link_libraries(RobotPositionNode
  ${catkin_LIBRARIES}
)

add_executable(RobotVelocityCommandNode src/RobotVelocityCommand.cpp)
target_link_libraries(RobotVelocityCommandNode
  ${catkin_LIBRARIES}
)
