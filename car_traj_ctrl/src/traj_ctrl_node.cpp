#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <cmath>

geometry_msgs::Pose2D pose;
void poseCallback(const geometry_msgs::Pose2D::ConstPtr& msg) {
    pose = *msg;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "traj_ctrl");
    ros::NodeHandle nh;

    double KPx, KPy, TIx, TIy, Ts, T, a;
    nh.getParam("KPx", KPx);
    nh.getParam("KPy", KPy);
    nh.getParam("TIx", TIx);
    nh.getParam("TIy", TIy);
    nh.getParam("Ts", Ts);
    nh.getParam("T", T);
    nh.getParam("a", a);

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    ros::Subscriber sub = nh.subscribe("car_pose", 1, poseCallback);

    double ix=0, iy=0;
    ros::Rate loop(1.0/Ts);
    double t=0;

    while (ros::ok()) {
        double xf = a * sin(2*M_PI/T*t);
        double yf = a * sin(2*M_PI/T*t) * cos(2*M_PI/T*t);

        double ex = xf - pose.x;
        double ey = yf - pose.y;

        ix += ex * Ts / TIx;
        iy += ey * Ts / TIy;

        geometry_msgs::Twist cmd;
        cmd.linear.x  = KPx*ex + ix;
        cmd.angular.z = KPy*ey + iy;

        pub.publish(cmd);

        t += Ts;
        ros::spinOnce();
        loop.sleep();
    }
}
