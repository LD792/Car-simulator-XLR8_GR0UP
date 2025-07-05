#ifndef CAR_H
#define CAR_H

extern const unsigned int car_masse = 1490;
extern const unsigned int wheel_radius = 0.26;
extern const float wheel_inertia = 2.9;


extern float wheel_torque(float engine_torque, float gear_ratio, float clutch_stat );

extern float wheels_angular_acc(float wheel_torque);

extern float wheel_rpm(float wheel_ang_velocity); 

extern float driving_force(float wheel_torque);

extern float car_acc(float driving_force); 

extern float car_velocity(float acceleration, float delta_time); 

extern float wheel_angular_velocity(float car_speed);


#endif