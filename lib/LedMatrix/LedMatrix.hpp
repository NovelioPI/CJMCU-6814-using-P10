#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <DMD2.h>

// Set Width to the number of displays wide you have
#define WIDTH 3

extern void matrix_init();
extern void matrix_display(float co, float nh3, float no2);
