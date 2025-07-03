#define _GNU_SOURCE
#include <stdlib.h>
#include <errno.h> 
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "engine.h"
#include "include/engine_data.h"


float get_torque(const TorqueEntry* table, unsigned int rpm){

    if (rpm < idle_rpm)
        return 0.0;

    //this implementation is just for begining after inchaallah i will add more realistic behavior
    if (rpm > rev_limiter)
        rpm = rev_limiter;

    if ((rpm - idle_rpm)%50 == 0){
        return table[(rpm - idle_rpm)/50].torque;
    }
    else
    {
        int lower_rpm = rpm - (rpm % 50);    
        int upper_rpm = lower_rpm + 50;
        int lower_index = (lower_rpm - idle_rpm) / 50;
        int upper_index = lower_index + 1;
        float torque_lower = table[lower_index].torque;
        float torque_upper = table[upper_index].torque;
        float t = (rpm - lower_rpm) / 50.0;
        float torque = torque_lower + (torque_upper - torque_lower) * t;
        return torque; 
    }

}


float angular_acc(float engine_torque){

    return engine_torque / engine_inertia;

}

float angular_velocity(float angular_acceleration, float delta_time){

    return angular_acceleration * delta_time;


}

unsigned int get_engine_rpm(float angular_velocity){

    return (unsigned int) round( angular_velocity * 30 / M_PI);


}

// next to do inchaallah: Gearbox logique 

