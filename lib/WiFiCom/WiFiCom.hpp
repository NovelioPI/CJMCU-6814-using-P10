#pragma once

#include <Arduino.h>

extern void wifi_init(const char *ssid, const char *pass);
extern void send_data(const char *server, String apiKey);