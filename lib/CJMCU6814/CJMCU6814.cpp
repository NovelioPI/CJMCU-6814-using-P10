#include <CJMCU6814.hpp>
#include <Arduino.h>

#define PIN_CO  A0
#define PIN_NH3 A1
#define PIN_NO2 A2

const float max_volts = 5.0;
const float max_analog_steps = 1023.0;

void CJMCU6814::sensor_init()
{
    // Serial.print("Calibrate sensor");
    pinMode(PIN_CO, INPUT);
    baseResCO = calibration(PIN_CO);

    pinMode(PIN_NH3, INPUT);
    baseResNH3 = calibration(PIN_NH3);

    pinMode(PIN_NO2, INPUT);
    baseResNO2 = calibration(PIN_NO2);

    // Serial.println(" [Done]");
    // Serial.println("--- Base Resistance ---");
    // Serial.print("CO : ");
    // Serial.println(baseResCO);
    // Serial.print("NH3 : ");
    // Serial.println(baseResNH3);
    // Serial.print("NO2 : ");
    // Serial.println(baseResNO2);

    delay(1000);
}

void CJMCU6814::sensor_read(float *co, float *nh3, float *no2)
{
    float resC0 = getRes(PIN_CO);
    float resNH3 = getRes(PIN_NH3);
    float resNO2 = getRes(PIN_NO2);

    float ratioCO = resC0 / baseResCO * (1023.0 - baseResCO) / (1023.0 - resC0);
    float ratioNH3 = resNH3 / baseResNH3 * (1023.0 - baseResNH3) / (1023.0 - resNH3);
    float ratioNO2 = resNO2 / baseResNO2 * (1023.0 - baseResNO2) / (1023.0 - resNO2);

    *co = pow (ratioCO, -1.179) * 4.385;
    *nh3 = pow (ratioNH3, 1.007) / 6.855;
    *no2 = pow (ratioNO2, -1.67) / 1.47;
}

float CJMCU6814::calibration(int pin)
{
	unsigned long time = millis();

	uint8_t delta = 1;
	float curr = 0;
    float prev = 0;
    float div = 0;
    float base = 0;

	// Calibrate
	do
	{
		unsigned long rs = 0;

		for (int i = 0; i <3; i ++)
		{
			rs += analogRead(pin);
            delay (1);
		}

		curr = rs / 3;
		div += (curr - prev);
        base = div / ((millis() - time)/1000);
        prev = curr;

        // Serial.print(".");
        delay(100);

	} while (abs (base - curr) > delta);

    return base;
}

float CJMCU6814::getRes(int pin)
{
    unsigned long rs = 0;
    int retry = 10;

    for (int i = 0; i<retry; i ++)
    {
        rs += analogRead(pin);
        delay(1);
    }

    return rs / retry;
}