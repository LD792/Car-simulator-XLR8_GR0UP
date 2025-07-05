#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h> 
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "engine.h"
#include "include/engine_data.h"
#include "car.h"

float get_torque(unsigned int rpm){

    if (rpm < idle_rpm)
        return 0.0;

    //this implementation is just for begining after inchaallah i will add more realistic behavior
    if (rpm > rev_limiter)
        rpm = rev_limiter;

    if ((rpm - idle_rpm)%50 == 0)
        return LAMBO_TORQUE_TABLE[(rpm - idle_rpm)/50].torque;
    
    else
    {
        int lower_rpm = rpm - (rpm % 50);    
        int upper_rpm = lower_rpm + 50;
        int lower_index = (lower_rpm - idle_rpm) / 50;
        int upper_index = lower_index + 1;
        float torque_lower = LAMBO_TORQUE_TABLE[lower_index].torque;
        float torque_upper = LAMBO_TORQUE_TABLE[upper_index].torque;
        float t = (rpm - lower_rpm) / 50.0;
        float torque = torque_lower + (torque_upper - torque_lower) * t;
        
        return torque; 
    }

}


float engine_angular_acc(float engine_torque)
{
    return engine_torque / engine_inertia;
}

float engine_angular_velocity(float angular_acceleration, float delta_time)
{
    return angular_acceleration * delta_time;
}

unsigned int get_engine_rpm(float angular_velocity)
{
    return (unsigned int) round( angular_velocity * 30 / M_PI);
}

// next to do inchaallah: Gearbox logique 
void update_transmission(unsigned int* curr_gear, unsigned int *curr_rpm, float* phase_timer, float* clutch_state, 
                         bool shift_up_request, bool shift_down_request, shift_phase* phase)
{
    static float transfered_torque = 0.0;
    static unsigned int new_gear = 0;

    switch (*phase)
    {
    
    case SHIFT_IDLE:
        if (shift_up_request || shift_down_request){
            *phase = SHIFT_DISENGAGING;
            *phase_timer = disengage_delay;
        }
    
    break;

    case SHIFT_DISENGAGING:
        
            *phase_timer -= 0.016; //60fps
            *clutch_state -= 0.016 / disengage_delay;
            transfered_torque = get_torque(curr_rpm) * (*clutch_state);

            if(*clutch_state <= 0.02){

                if(shift_up_request && *curr_gear != max_gear)
                    new_gear = *curr_gear + 1;
                else if(shift_down_request && *curr_gear != 0)
                    new_gear = *curr_gear - 1;
                
                *phase_timer = rev_match_delay;
                *phase = SHIFT_REV_MATCH;
            }
    break;
        
    case SHIFT_REV_MATCH:
        *phase_timer -= 0.016;
        float wheel_moment = wheel_torque(transfered_torque, GEAR_RATIOS_TABLE[new_gear], *clutch_state);
        float mvt_force = driving_force(wheel_moment);
        float car_acceleration = car_acc(mvt_force);
        float car_speed = car_velocity(car_acceleration, 0.016);
        float wheel_ang_speed = wheel_angular_velocity(car_speed);

        int target_engine_rpm = wheel_rpm(wheel_ang_speed) * GEAR_RATIOS_TABLE[new_gear] * final_drive ;
        float step = (target_engine_rpm - *curr_rpm) * (0.016 / rev_match_delay);
        if(*curr_rpm <= target_engine_rpm)
            *curr_rpm = (unsigned int)round(*curr_rpm + step);
        else if (*curr_rpm >= target_engine_rpm)
            *curr_rpm = (unsigned int)round(*curr_rpm - step);

        if(abs(target_engine_rpm - *curr_rpm) <= 50){ 
            *phase_timer = engaging_delay;
            *phase = SHIFT_ENGAGING;

        } 
    break;

    case SHIFT_ENGAGING:
        *phase_timer -= 0.016;
        *clutch_state += 0.016 / engaging_delay;
        if (*curr_gear != new_gear)
            *curr_gear = new_gear;
        if(0.98 <= *clutch_state && *clutch_state <= 1){
            *phase_timer = 0.0;
            *phase = SHIFT_COMPLETE;
        }
    break;
    
    case SHIFT_COMPLETE:
        *phase = SHIFT_IDLE;
    
    break;
    default: *phase = SHIFT_IDLE; break;
    }
    
    /*
    better approach will be creating and using this struct.
    (we just implement one car so the current code steal fine inchaallah)
    typedef struct {
    unsigned int curr_gear;
    unsigned int target_gear;
    float clutch_state;
    float phase_timer;
    float transfered_torque;
    shift_phase phase;
    } TransmissionState;
    
    */   
}



