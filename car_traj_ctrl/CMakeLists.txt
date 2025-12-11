cmake_minimum_required(VERSION 3.0.2)
project(car_traj_ctrl)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(traj_ctrl_node src/traj_ctrl_node.cpp)
target_link_libraries(traj_ctrl_node ${catkin_LIBRARIES})
