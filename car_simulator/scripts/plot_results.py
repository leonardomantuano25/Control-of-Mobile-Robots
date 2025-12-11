#!/usr/bin/env python
import rosbag
import matplotlib.pyplot as plt

bag = rosbag.Bag("sim.bag")
x=[]; y=[]

for t, msg, in bag.read_messages("/car_pose"):
    x.append(msg.x)
    y.append(msg.y)

plt.plot(x, y)
plt.xlabel("x [m]")
plt.ylabel("y [m]")
plt.title("Car trajectory")
plt.show()
