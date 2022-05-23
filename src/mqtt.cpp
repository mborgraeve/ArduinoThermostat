#include <ESP8266WiFi.h>
#include "../lib/mqtt/src/EspMQTTClient.h"

const char *ssid = "BandelBorgraeveAN"; // remplacer par le SSID de votre WiFi
const char *password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi

EspMQTTClient mqttClient(
        "10.0.0.223",  // MQTT Broker server ip
        1883,
        "mqtt",   // Can be omitted if not needed
        "Kz2kXddmXz4n39AXM97i",   // Can be omitted if not needed
        "nodeMcuTest"      // Client name that uniquely identify your device
);


void setup(void) {
    Serial.begin(115200);
    Serial.println("Initializing...");
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println("Wifi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // on affiche l'adresse IP qui nous a ete attribuee
    Serial.println("");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void onConnectionEstablished() {

    mqttClient.subscribe("mytopic/test", [](const String &payload) {
        Serial.println(payload);
    });

    mqttClient.publish("mytopic/test", "This is a message");
}

void loop(void) {
    Serial.println("Looping...");
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Client publish");
    mqttClient.publish("mytopic/test", "messagePublished from NodeMcu !");
    Serial.println("Client loop");
    mqttClient.loop();
}
