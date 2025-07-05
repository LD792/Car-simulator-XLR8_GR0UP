#define _GNU_SOURCE
#include <math.h>
#include "car.h"
#include "engine.h"
#include "engine_data.h"

float wheel_torque(float engine_torque, float gear_ratio, float clutch_stat ){
    return engine_torque * gear_ratio * clutch_stat * final_drive;
}

float wheels_angular_acc(float wheel_torque){
    return wheel_torque / wheel_inertia;
}

float wheel_rpm(float wheel_ang_velocity){
    return wheel_ang_velocity * 30 / M_PI;
}

float driving_force(float wheel_torque){
    return wheel_torque / wheel_radius;
}

float car_acc(float driving_force){
    return driving_force / car_masse;
} 

float car_velocity(float acceleration, float delta_time){
    return acceleration * delta_time * 3.6;
}

float wheel_angular_velocity(float car_speed){
    return car_speed / wheel_radius ;
}