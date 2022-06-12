#include <Arduino.h>
#include <CJMCU6814.hpp>
#include <DataTransaction.hpp>
#include <LedMatrix.hpp>

// #define DEBUG

float co, nh3, no2;

CJMCU6814 enose;

void setup()
{
    Serial.begin(9600);
    enose.sensor_init();
    matrix_init();
}

void loop()
{
    enose.sensor_read(&co, &nh3, &no2);

#ifdef DEBUG
    Serial.print("CO:");
    Serial.print(co);
    Serial.print("  ");
    Serial.print("NH3:");
    Serial.print(nh3);
    Serial.print("  ");
    Serial.print("NO2:");
    Serial.print(no2);
    Serial.println();
#else
    write_data(co);
    write_data(nh3);
    write_data(no2);
#endif

    matrix_display(co, nh3, no2);
}