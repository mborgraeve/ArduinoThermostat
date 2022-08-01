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

#define DHT_ACTIVE true
#define DHT11_PIN 2

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
    #endif //DEBUG

    getMqttClient()->publish("mytopic/test", "messagePublished from NodeMcu !");

    DhtResult dhtTemp = readDht();
    Serial.println("DHT Check:");
    Serial.println(dhtTemp.chk);
    Serial.println("Temperature:");
    Serial.println(dhtTemp.temperature);
    Serial.println("Humidity:");
    Serial.println(dhtTemp.humidity);
    Serial.println("Client loop");

    getMqttClient()->loop();

    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(3000);
}
