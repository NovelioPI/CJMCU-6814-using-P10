#pragma once

class CJMCU6814
{
public:
    CJMCU6814() {}
    ~CJMCU6814() {}

    void sensor_init();
    void sensor_read(float *co, float *nh3, float *no2);

    float calibration(int pin);
    float getRes(int pin);

private:
    float baseResCO = 0;
    float baseResNH3 = 0;
    float baseResNO2 = 0;
};
