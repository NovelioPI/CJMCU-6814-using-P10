#include <WiFiCom.hpp>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DataTransaction.hpp>

void wifi_init(const char *ssid, const char *pass)
{
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
}

void send_data(const char *server, String apiKey)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        http.begin(client, server);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        String httpRequestData = 
            "api_key=" + apiKey +
            "&GAS1=" + read_data() +
            "&GAS2=" + read_data() +
            "&GAS3=" + read_data() +
            "";

        int resp = http.POST(httpRequestData);

        // Serial.println(resp);

        http.end();
    }
}