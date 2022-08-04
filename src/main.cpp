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
    Serial.println("Finished initializing...");
}

void loop() {
    #ifdef DEBUG
    Serial.println("Looping...");
    #endif //DEBUG

    digitalWrite(LED_BUILTIN, HIGH);

    #ifdef DEBUG
    Serial.println("Client publish");
    getMqttClient()->publish(MQTT_TOPIC_MESSAGES, "messagePublished from NodeMcu !");
    #endif //DEBUG

    DhtResult dhtTemp = readDht();

    #ifdef DEBUG
    Serial.println("Temperature:");
    Serial.println(dhtTemp.temperature);
    Serial.println("Humidity:");
    Serial.println(dhtTemp.humidity);
    #endif //DEBUG

    getMqttClient()->publish(MQTT_TOPIC_TEMPERATURE, String(dhtTemp.temperature));
    getMqttClient()->publish(MQTT_TOPIC_HUMIDITY, String(dhtTemp.humidity));

    #ifdef DEBUG
    Serial.println("Client loop");
    #endif //DEBUG
    getMqttClient()->loop();

    digitalWrite(LED_BUILTIN, LOW);
    delay(SLEEP_TIME);
}
