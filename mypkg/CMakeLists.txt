cmake_minimum_required(VERSION 2.8.3)
project(mypkg)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(RaspberryPI src/RaspberryPI.cpp)

add_dependencies(RaspberryPI mypkg_generate_messages_spp)

target_link_libraries(RaspberryPI
  ${catkin_LIBRARIES}
)
