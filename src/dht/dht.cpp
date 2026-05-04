
#include "configuration.h"
#include "../configuration.h"

#ifdef DHT_ACTIVE

#include "dht.h"

DHT dhtSketchInstance(DHT_PIN, DHT_TYPE);

void setupDht() {
    LOG_IF_DEBUG("DHT type/port ")
    LOG_IF_DEBUG(DHT_TYPE)
    LOG_IF_DEBUG_LN(DHT_PIN)
    dhtSketchInstance.begin();
}

DhtResult readDht() {
    float temp = dhtSketchInstance.readTemperature(false, false);
    float hum = dhtSketchInstance.readHumidity(false);
    return {temp, hum};
}

#endif //DHT_ACTIVE
