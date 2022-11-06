#include <Arduino.h>
#include "configuration.h"

#ifdef WIFI_ACTIVE
#include "wifi/wifi.h"
#endif //WIFI_ACTIVE

#ifdef MQTT_ACTIVE
#include "mqtt/mqtt.h"
#endif //MQTT_ACTIVE

#ifdef DHT_ACTIVE
#include "./dht/dht.h"
#endif //DHT_ACTIVE

#ifdef THERMOSTAT_ACTIVE
#include "./thermostat/thermostat.h"

Thermostat *thermostat;
Timer *timer;
#endif //THERMOSTAT_ACTIVE

void subscribeThermostat();

bool doSubscribe();

void resetLoop();

#ifdef RESET
int loopsBeforeReset = USER_LOOPS_BEFORE_RESET;
#endif //RESET

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println("Initializing...");

    #ifdef DEBUG_LED
    pinMode(PIN_LED, OUTPUT);
    #endif //DEBUG_LED

    #ifdef DHT_ACTIVE
    setupDht();
    #endif //DHT_ACTIVE

    #ifdef WIFI_ACTIVE
    setupWifi();
    #endif //WIFI_ACTIVE

    #ifdef MQTT_ACTIVE
    setupMqtt();
    #endif //MQTT_ACTIVE

    #ifdef TIMER_ACTIVE
    timer = new Timer();
    #endif //TIMER_ACTIVE

    #ifdef THERMOSTAT_ACTIVE
    thermostat = new Thermostat(timer);
        #ifdef MQTT_ACTIVE
    subscribeThermostat();
        #endif //MQTT_ACTIVE
    #endif //THERMOSTAT_ACTIVE

    Serial.println("Finished initializing...");
}

#ifdef THERMOSTAT_ACTIVE
void subscribeThermostat() {
    getMqttClient()->setOnConnectionEstablishedCallback([]() {
        getMqttClient()->subscribe(TARGET_TEMPERATURE_TOPIC, [](const String &payload) {
            LOG_IF_DEBUG_LN("Received new target temperature:")
            LOG_IF_DEBUG_LN(payload)
            thermostat->updateTargetTemperature(payload.toFloat());
        });
    });
}
#endif //THERMOSTAT_ACTIVE

void switchLedAndDelay() {
    #ifdef DEBUG_LED
    digitalWrite(PIN_LED, HIGH);
    delay(LED_UP_TIME);
    digitalWrite(PIN_LED, LOW);
    delay(REMAINING_SLEEP_TIME);
    #else
    delay(SLEEP_TIME);
    #endif //DEBUG_LED
}

short counter = 0;

void loop() {
    if (counter * SLEEP_TIME < USER_LOOP_TIME) {
        ++counter;
        TRACE_LN("skipping...")
    } else {
        #ifdef RESET
        resetLoop();
        #endif //RESET

        counter = 0;
        LOG_IF_DEBUG_LN("Looping...")

        #ifdef LED_DEBUG
        digitalWrite(PIN_LED, HIGH)
        #endif //LED_DEBUG

        #ifdef DEBUG_SERIAL
        LOG_IF_DEBUG_LN("Client publish")
        getMqttClient()->publish(MQTT_TOPIC_MESSAGES, "messagePublished from NodeMcu !")
        #endif //DEBUG_SERIAL

        DhtResult dhtTemp = readDht();
        String temp = String(dhtTemp.temperature);
        String hum = String(dhtTemp.humidity);

        LOG_IF_DEBUG("Temperature:")
        LOG_IF_DEBUG_LN(temp)
        LOG_IF_DEBUG("Humidity:")
        LOG_IF_DEBUG_LN(hum)

        getMqttClient()->publish(MQTT_TOPIC_TEMPERATURE, temp);
        getMqttClient()->publish(MQTT_TOPIC_HUMIDITY, hum);

        #ifdef THERMOSTAT_ACTIVE
        thermostat->loop(dhtTemp.temperature);
        getMqttClient()->publish(MQTT_TOPIC_THERMOSTAT_TEMPERATURE, String(thermostat->readValue()));
        getMqttClient()->publish(MQTT_TOPIC_THERMOSTAT_HEATING, String(thermostat->shouldHeat()));
        #endif //THERMOSTAT_ACTIVE


        LOG_IF_DEBUG_LN("-----------------------------------------------------------------------------------")
    }
    TRACE("Mqtt loop")
    getMqttClient()->loop();
    switchLedAndDelay();
    TRACE("End of loop.")
}

#ifdef RESET

void resetLoop() {
    if (loopsBeforeReset > 0) {
        loopsBeforeReset--;
    } else {
        LOG_IF_DEBUG_LN("Will restart the chip.")
        loopsBeforeReset = USER_LOOPS_BEFORE_RESET;
        EspClass::restart();
    }
}

#endif //RESET

