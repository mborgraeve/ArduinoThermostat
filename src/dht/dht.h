
#include "configuration.h"

#ifdef DHT_ACTIVE

#if !defined(DHT_PIN) || !defined(DHT_TYPE)
#error DHT_PIN and DHT_TYPE should be defined.
#endif

#ifndef ARDUINOTHERMOSTAT_DHT_H
#define ARDUINOTHERMOSTAT_DHT_H

#include <Adafruit_Sensor.h>
#include <DHT.h>

struct DhtResult {
    float temperature;
    float humidity;
};
DHT dhtSketchInstance(DHT_PIN, DHT_TYPE);

void setupDht();

DhtResult readDht();

#endif //ARDUINOTHERMOSTAT_DHT_H
#endif //DHT_ACTIVE