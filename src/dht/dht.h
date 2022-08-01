//
// Created by matth on 2022-07-27.
//
#ifdef DHT_ACTIVE

#if defined(DHT11_PIN) && defined(DHT_22_PIN) || !defined(DHT11_PIN) && !defined(DHT_22_PIN)
#error Exactly one of DHT11_PIN or DHT22_PIN should be defined.
#endif

#ifndef ARDUINOTHERMOSTAT_DHT_H
#define ARDUINOTHERMOSTAT_DHT_H
#include "../lib/DHTLib/dht.h"


struct DhtResult{
    int temperature;
    int humidity;
    int chk;
};

void setupDht();
DhtResult readDht();

#endif //ARDUINOTHERMOSTAT_DHT_H
#endif //DHT