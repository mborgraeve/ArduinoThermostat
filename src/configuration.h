
#ifndef ARDUINOTHERMOSTAT_CONFIGURATION_H
#define ARDUINOTHERMOSTAT_CONFIGURATION_H


#define BAUD_RATE 115200
#define USER_LOOP_TIME 10e3 //10s
#define SLEEP_TIME 10
#define LED_UP_TIME 5
//#define DEBUG_SERIAL
//#define DEBUG_TRACE
//#define DEBUG_LED
#define REMAINING_SLEEP_TIME SLEEP_TIME - LED_UP_TIME

#ifdef DEBUG_SERIAL
    #define LOG_IF_DEBUG_LN(l){Serial.println(l);}
    #define LOG_IF_DEBUG(l){Serial.print(l);}
    #ifdef DEBUG_TRACE
        #define TRACE(l) LOG_IF_DEBUG(l)
        #define TRACE_LN(l)  LOG_IF_DEBUG_LN(l)
    #else
        #define TRACE(l){}
        #define TRACE_LN(l){}
    #endif //DEBUG_TRACE
#else
    #define LOG_IF_DEBUG_LN(l){}
    #define LOG_IF_DEBUG(l){}
    #define TRACE(l){}
    #define TRACE_LN(l){}
#endif // DEBUG_SERIAL

#ifdef DEBUG_LED
    #define PIN_LED 16
#endif //DEBUG_LED

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a < b ? b : a

#define RESET
#ifdef RESET
#define USER_LOOPS_BEFORE_RESET 6 * 60 * 60 * 1000 / USER_LOOP_TIME
#endif //RESET

#define WIFI_ACTIVE
#ifdef WIFI_ACTIVE
    #define WIFI_SSID "BandelBorgraeveAN"
    #define WIFI_PWD "coucoucnous"
#endif //WIFI_ACTIVE

#define MQTT_ACTIVE
#ifdef MQTT_ACTIVE
    #define MQTT_SERVER_HOST "10.0.0.223"
    #define MQTT_SERVER_PORT 1883
    #define MQTT_USER "mqtt"
    #define MQTT_PWD "Kz2kXddmXz4n39AXM97i"
    #define MQTT_CLIENT_NAME "nodeMcuTest"
    #define MQTT_TOPIC_UPDATE "topicUpdate"
    #define MQTT_TOPIC_MESSAGES "mytopic/test"
    #define MQTT_TOPIC_TEMPERATURE "gas.temperature"
    #define MQTT_TOPIC_HUMIDITY "gas.humidity"
    #define MQTT_RECONNECT_DELAY_MS 500
#endif //MQTT_ACTIVE

#define DHT_ACTIVE
    #ifdef DHT_ACTIVE
    #define DHT_PIN 4
    #define DHT_TYPE DHT22
#endif //DHT_ACTIVE

#define THERMOSTAT_ACTIVE
#ifdef THERMOSTAT_ACTIVE
    #define THERMOSTAT_CONTROL_PIN 5
    #define ALPHA 0.05
    #define UPDATE_DELAY 1
    #define DEFAULT_TARGET 13.0
    #define HYSTERESIS_DELTA 1.0
    #define INITIAL_VALUE 15
    #ifdef MQTT_ACTIVE
        #define TARGET_TEMPERATURE_TOPIC "gas.target.temperature"
    #endif //MQTT_ACTIVE
    #define MQTT_TOPIC_THERMOSTAT_TEMPERATURE "gas.thermostat.temperature"
    #define MQTT_TOPIC_THERMOSTAT_HEATING "gas.thermostat.heating"
#endif //THERMOSTAT ACTIVE

#define TIMER_ACTIVE
#ifdef TIMER_ACTIVE
    #define TIME_SERVER "us.pool.ntp.org"
#endif //TIMER_ACTIVE

#endif //ARDUINOTHERMOSTAT_CONFIGURATION_H
