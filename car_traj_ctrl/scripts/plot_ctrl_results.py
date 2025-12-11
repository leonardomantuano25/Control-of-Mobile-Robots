#!/usr/bin/env python
import rosbag
import matplotlib.pyplot as plt

bag = rosbag.Bag("ctrl.bag")
x=[]; y=[]; xr=[]; yr=[]

for t, msg in bag.read_messages("/car_pose"):
    x.append(msg.x)
    y.append(msg.y)
for t, msg in bag.read_messages("/ref_traj"):
    xr.append(msg.x)
    yr.append(msg.y)

plt.plot(xr, yr, label="reference")
plt.plot(x, y, label="actual")
plt.legend()
plt.show()
