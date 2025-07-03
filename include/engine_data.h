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

#endif 