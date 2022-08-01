
#include "configuration.h"

#ifdef DHT_ACTIVE

#include "dht.h"

void setupDht() {
#ifdef DHT11_PIN
    pinMode(DHT11_PIN, INPUT);
#elif defined(DHT22_PIN)
    pinMode(DHT22_PIN, INPUT);
#endif
}

DhtResult readDht() {
    int chk;
#ifdef DHT11_PIN
    chk = DHT.read11(DHT11_PIN);
#elif defined(DHT22_PIN)
    chk = DHT.read22(DHT22_PIN);
#endif
    return {DHT.temperature, DHT.humidity, chk};

}

#endif //DHT_ACTIVE
