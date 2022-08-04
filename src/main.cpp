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

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println("Initializing...");

    pinMode(LED_BUILTIN, OUTPUT);

    #ifdef DHT_ACTIVE
    setupDht();
    #endif //DHT_ACTIVE

    #ifdef WIFI_ACTIVE
    setupWifi();
    #endif //WIFI_ACTIVE

    #ifdef MQTT_ACTIVE
    setupMqtt();
    #endif //MQTT_ACTIVE

    Serial.println("Finished initializing...");
}


void switchLedAndDelay() {
    #ifdef DEBUG
    digitalWrite(LED_BUILTIN, HIGH);
    delay(LED_UP_TIME);
    digitalWrite(LED_BUILTIN, LOW);
    delay(REMAINING_SLEEP_TIME);
    #else
    delay(SLEEP_TIME);
    #endif //DEBUG
}

short counter = 0;

void loop() {
    if (counter * SLEEP_TIME < USER_LOOP_TIME) {
        ++counter;
        LOG_IF_DEBUG("skipping...");
    } else {
        counter = 0;
        LOG_IF_DEBUG("Looping...");

        digitalWrite(LED_BUILTIN, HIGH);

        #ifdef DEBUG
        LOG_IF_DEBUG("Client publish");
        getMqttClient()->publish(MQTT_TOPIC_MESSAGES, "messagePublished from NodeMcu !");
        #endif //DEBUG

        DhtResult dhtTemp = readDht();
        String temp = String(dhtTemp.temperature);
        String hum = String(dhtTemp.humidity);

        LOG_IF_DEBUG("Temperature:");
        LOG_IF_DEBUG(temp);
        LOG_IF_DEBUG("Humidity:");
        LOG_IF_DEBUG(hum);

        getMqttClient()->publish(MQTT_TOPIC_TEMPERATURE, temp);
        getMqttClient()->publish(MQTT_TOPIC_HUMIDITY, hum);

    }
    LOG_IF_DEBUG("Mqtt loop");
    getMqttClient()->loop();
    switchLedAndDelay();
    LOG_IF_DEBUG("End of loop.")
}

