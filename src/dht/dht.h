#include "configuration.h"

#ifdef DHT_ACTIVE

#ifndef ARDUINOTHERMOSTAT_DHT_H
#define ARDUINOTHERMOSTAT_DHT_H

#if !defined(DHT_PIN) || !defined(DHT_TYPE)
#error DHT_PIN and DHT_TYPE should be defined.
#endif

#include <Adafruit_Sensor.h>
#include <DHT.h>

struct DhtResult {
    float temperature;
    float humidity;
};

void setupDht();

DhtResult readDht();

#endif //DHT_ACTIVE
#endif //ARDUINOTHERMOSTAT_DHT_H
