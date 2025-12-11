cmake_minimum_required(VERSION 3.0.2)
project(car_simulator)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
)

find_package(Boost REQUIRED)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_executable(car_sim_node src/car_sim_node.cpp)
target_link_libraries(car_sim_node ${catkin_LIBRARIES})

add_executable(test_input_node src/test_input_node.cpp)
target_link_libraries(test_input_node ${catkin_LIBRARIES})
