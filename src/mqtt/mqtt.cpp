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

#endif //MQTT_ACTIVE
