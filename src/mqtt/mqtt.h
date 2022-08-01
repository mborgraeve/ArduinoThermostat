#include "configuration.h"

#ifdef MQTT_ACTIVE

#if !defined(MQTT_SERVER_HOST) || !defined(MQTT_SERVER_PORT) || !defined(MQTT_USER) || !defined(MQTT_PWD) || !defined(MQTT_CLIENT_NAME) || !defined(MQTT_TOPIC_UPDATE)
#error "Both WIFI_SSID and WIFI_PWD should be defined"
#endif

#ifndef ARDUINOTHERMOSTAT_MQTT_H
#define ARDUINOTHERMOSTAT_MQTT_H

#include <EspMQTTClient.h>

EspMQTTClient *getMqttClient();

void onConnectionEstablished();

#endif //ARDUINOTHERMOSTAT_MQTT_H
#endif //MQTT_ACTIVE
