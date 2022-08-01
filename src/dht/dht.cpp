
#include "configuration.h"

#ifdef DHT_ACTIVE

#include "dht.h"

void setupDht() {
    dhtSketchInstance.begin();
}

DhtResult readDht() {
    float temp = dhtSketchInstance.readTemperature(false, false);
    float hum = dhtSketchInstance.readHumidity(false);
    return {temp, hum};

}

#endif //DHT_ACTIVE
