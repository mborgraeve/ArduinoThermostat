//
// Created by matth on 2022-07-27.
//
#ifdef WIFI_ACTIVE
#include "wifi.h"

void setupWifi(){

    Serial.println("Wifi Initializing");
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // on affiche l'adresse IP qui nous a ete attribuee
    Serial.println("o");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
#endif //WIFI_ACTIVE