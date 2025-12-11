#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <boost/numeric/odeint.hpp>

using namespace boost::numeric::odeint;

struct CarModel {
    double a, b, m, Iz, Caf, Car;

    void operator()(const std::vector<double> &x, std::vector<double> &dxdt, const double /*t*/) {
        double X = x[0], Y = x[1], yaw = x[2], vx = x[3], vy = x[4], r = x[5];

        double delta = x[6];
        double Fyf = -Caf * (vy + a*r - vx * delta) / vx;
        double Fyr = -Car * (vy - b*r) / vx;

        dxdt[0] = vx * cos(yaw) - vy * sin(yaw);
        dxdt[1] = vx * sin(yaw) + vy * cos(yaw);
        dxdt[2] = r;
        dxdt[3] = 0.0;
        dxdt[4] = (Fyf + Fyr) / m - vx * r;
        dxdt[5] = (a*Fyf - b*Fyr) / Iz;
        dxdt[6] = 0.0;
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "car_sim");
    ros::NodeHandle nh;

    double a, b, m, Iz, Caf, Car;
    nh.getParam("a", a);
    nh.getParam("b", b);
    nh.getParam("mass", m);
    nh.getParam("Iz", Iz);
    nh.getParam("Caf", Caf);
    nh.getParam("Car", Car);

    CarModel model {a, b, m, Iz, Caf, Car};
    std::vector<double> state(7, 0.0);

    ros::Publisher pub = nh.advertise<geometry_msgs::Pose2D>("car_pose", 1);
    ros::Rate loop(100);

    runge_kutta4<std::vector<double>> stepper;

    while (ros::ok()) {
        stepper.do_step(model, state, 0.01);
        geometry_msgs::Pose2D msg;
        msg.x = state[0];
        msg.y = state[1];
        msg.theta = state[2];
        pub.publish(msg);
        ros::spinOnce();
        loop.sleep();
    }
}
