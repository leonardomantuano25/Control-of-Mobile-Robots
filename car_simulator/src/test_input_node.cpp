#include <ros/ros.h>
#include <std_msgs/Float64.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_input");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::Float64>("steering_cmd", 1);
    ros::Rate loop(1);

    while (ros::ok()) {
        std_msgs::Float64 msg;
        msg.data = 0.1;  // step input
        pub.publish(msg);
        ros::spinOnce();
        loop.sleep();
    }
}
