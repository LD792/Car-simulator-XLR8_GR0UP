#ifndef ENGINE_DATA_H
#define ENGINE_DATA_H

#include <stddef.h> 

// Define the structure for each RPM-Torque pair
typedef struct {
    unsigned int rpm;   
    double torque;   
} TorqueEntry;

// Declare the constant array containing the torque lookup table data.
// is provided in another source file (specifically, torque_lookup_table.c).
extern const TorqueEntry LAMBO_TORQUE_TABLE[];

// Declare the constant for the size of the torque table array.
extern const size_t LAMBO_TORQUE_TABLE_SIZE;

//Gear ratios table.
extern const float GEAR_RATIOS_TABLE[] = {3.909, 2.438, 1.833, 1.467, 1.250, 1.034, 0.846, 
    3.529}; // Reverse.
extern const float final_drive = 3.480;

typedef enum {
    SHIFT_IDLE,
    SHIFT_DISENGAGING,
    SHIFT_REV_MATCH,
    SHIFT_ENGAGING,
    SHIFT_COMPLETE
}shift_phase;

#endif 