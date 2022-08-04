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
    String str = String();
    #ifdef DEBUG
    Serial.println("Looping...");
    #endif //DEBUG

    digitalWrite(LED_BUILTIN, HIGH);

    #ifdef DEBUG
    Serial.println("Client publish");
    #endif //DEBUG

    getMqttClient()->publish(MQTT_TOPIC_MESSAGES, "messagePublished from NodeMcu !");

    DhtResult dhtTemp = readDht();
    Serial.println("Temperature:");
    Serial.println(dhtTemp.temperature);
    Serial.println("Humidity:");
    Serial.println(dhtTemp.humidity);

    getMqttClient()->publish(MQTT_TOPIC_TEMPERATURE, str+dhtTemp.temperature);
    getMqttClient()->publish(MQTT_TOPIC_HUMIDITY, str+dhtTemp.humidity);

    Serial.println("Client loop");

    getMqttClient()->loop();

    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(3000);
}
