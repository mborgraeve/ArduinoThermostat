#ifdef WIFI_ACTIVE

#if !defined(WIFI_SSID) || !defined(WIFI_PWD)
#error "Both WIFI_SSID and WIFI_PWD should be defined"
#endif

#ifndef ARDUINOTHERMOSTAT_WIFI_H
#define ARDUINOTHERMOSTAT_WIFI_H
#include <ESP8266WiFi.h>

void setupWifi();
#endif //ARDUINOTHERMOSTAT_WIFI_H
#endif