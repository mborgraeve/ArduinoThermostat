#include "configuration.h"

#ifdef WIFI_ACTIVE
#include "wifi.h"

void setupWifi(){

    Serial.println("Wifi Initializing");
    WiFi.begin(WIFI_SSID, WIFI_PWD);
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