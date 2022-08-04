
#ifndef ARDUINOTHERMOSTAT_CONFIGURATION_H
#define ARDUINOTHERMOSTAT_CONFIGURATION_H


#define BAUD_RATE 115200
#define DEBUG true
#define WIFI_ACTIVE true
#define WIFI_SSID "BandelBorgraeveAN"
#define WIFI_PWD "coucoucnous"

#define MQTT_ACTIVE true
#define MQTT_SERVER_HOST "10.0.0.223"
#define MQTT_SERVER_PORT 1883
#define MQTT_USER "mqtt"
#define MQTT_PWD "Kz2kXddmXz4n39AXM97i"
#define MQTT_CLIENT_NAME "nodeMcuTest"
#define MQTT_TOPIC_UPDATE "topicUpdate"
#define MQTT_TOPIC_MESSAGES "mytopic/test"
#define MQTT_TOPIC_TEMPERATURE "test.temperature"
#define MQTT_TOPIC_HUMIDITY "test.humidity"

#define DHT_ACTIVE true
#ifdef DHT_ACTIVE
#include <DHT.h>
#define DHT_PIN 2
#define DHT_TYPE DHT11
#endif //DHT_ACTIVE

#endif //ARDUINOTHERMOSTAT_CONFIGURATION_H
