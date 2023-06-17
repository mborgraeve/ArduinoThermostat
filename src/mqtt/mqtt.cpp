#include "configuration.h"

#ifdef MQTT_ACTIVE

#include "mqtt.h"

EspMQTTClient mqttClient(
        MQTT_SERVER_HOST,
        MQTT_SERVER_PORT,
        MQTT_USER,
        MQTT_PWD,
        MQTT_CLIENT_NAME
);

void onConnectionEstablished() {
    String messageStart = "Connection established for device [";
    String messageEnd = "]";
    getMqttClient()->publish(MQTT_TOPIC_UPDATE, messageStart + MQTT_CLIENT_NAME + messageEnd);
}

void setupMqtt() {
    #ifdef DEBUG_TRACE
    getMqttClient()->enableDebuggingMessages(true);
    #endif //DEBUG_TRACE
    #ifdef DEBUG_SERIAL
    getMqttClient()->enableDebuggingMessages(true);
    #endif //DEBUG_SERIAL
    getMqttClient()->setMqttReconnectionAttemptDelay(MQTT_RECONNECT_DELAY_MS);
}

EspMQTTClient* getMqttClient(){
    return &mqttClient;
}

#endif //MQTT_ACTIVE
