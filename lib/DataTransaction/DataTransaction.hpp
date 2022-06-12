#pragma once

#include <Arduino.h>

typedef union {
    float floatingPoint;
    uint8_t binary[4];
} BinaryFloat;

extern void write_data(float data);
extern float read_data();