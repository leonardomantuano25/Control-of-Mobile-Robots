# Mobile Robots Project – Car Simulator and Trajectory Control

## Overview
This project implements a simulation and control framework for a car-like robot using ROS Melodic.  
The robot is modeled using a single-track (bicycle) model with either linear or Fiala tyre models.  
A trajectory tracking controller based on feedback linearization and PI control is implemented and tested on an 8-shaped reference trajectory.

The project is composed of two ROS packages:
- `car_simulator`
- `car_traj_ctrl`

---

## Package: car_simulator

### Description
This package simulates the dynamics of a car-like robot using the single-track dynamic model.  
The numerical integration is performed using the Boost Odeint library.

### Nodes
- **simulator_node**  
  Simulates the robot dynamics and publishes the vehicle state.
- **test_input_node**  
  Sends simple test inputs (e.g. step commands) to the simulator to verify model behavior.

### Files and Folders
- `config/parameters.yaml`  
  Contains vehicle parameters (mass, yaw inertia, geometry, tyre parameters, friction coefficient).
- `launch/simulator.launch`  
  Launches the simulator and the test input node.
- `scripts/plot_results.py`  
  Python script to plot simulation results from a ROS bag file.

---

## Package: car_traj_ctrl

### Description
This package implements a trajectory tracking controller for the car-like robot.  
The controller is composed of:
- Feedback linearization based on the bicycle kinematic model
- PI controller with velocity feed-forward
- Forward Euler discretization

The reference trajectory is an 8-shaped path.

### Nodes
- **trajectory_controller_node**  
  Generates the reference trajectory and computes the control inputs (velocity and steering).

### Files and Folders
- `config/parameters.yaml`  
  Contains model parameters and controller gains.
- `launch/traj_ctrl.launch`  
  Launches the simulator together with the trajectory tracking controller.
- `scripts/plot_tracking_results.py`  
  Python script to plot reference trajectory, actual trajectory, tracking errors and control inputs.

---

## Reference Trajectory
The reference trajectory is defined as:

x = a * sin(2πt / T)  
y = a * sin(2πt / T) * cos(2πt / T)

where:
- a = 2 m
- T is defined in the parameter file

---

## Controller Parameters
The following parameters are tuned:
- Proportional gains: `KPx`, `KPy`
- Integral time constants: `TIx`, `TIy`
- Sampling time: `Ts`

The tuning is performed in two steps:
1. Initial tuning using standard control theory tools.
2. Refinement through simulation-based analysis.

---

## How to Run

### Simulator Test
```bash
roslaunch car_simulator simulator.launch
```

### Trajectory Tracking Test
```bash
roslaunch car_traj_ctrl traj_ctrl.launch
```

### Plotting Results
After recording a ROS bag file, run:
```bash
python3 scripts/plot_results.py
```
or
```bash
python3 scripts/plot_tracking_results.py
```

The scripts generate:

- Reference and actual trajectories
- X and Y tracking errors
- Control inputs (velocity and steering)
- Lateral tyre forces (for Fiala tyre model)

---

## Notes
- The project is developed and tested using ROS Melodic.
- Both linear and Fiala tyre models are supported.
- For advanced tests, the trajectory period T is reduced by 25% as required by the assignment.
- All results and tuning choices are discussed in the accompanying PDF report.


