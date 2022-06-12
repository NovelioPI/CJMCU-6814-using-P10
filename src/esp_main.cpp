#include <Arduino.h>
#include <WiFiCom.hpp>

const char *ssid = "Hehe";
const char *pass = "apahayoo";

const char *server = "http://enose-ypti.masuk.id/post-polutant-data.php";
const char *apiKey = "h8ehY7a3Ms21";

void setup()
{
    // Setup Serial
    Serial.begin(9600);
    delay(10);

    // Setup WiFi
    wifi_init(ssid, pass);
}

void loop()
{
    if (Serial.available())
        send_data(server, apiKey);
}