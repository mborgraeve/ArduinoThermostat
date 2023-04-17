//
// Created by matth on 2023-01-02.
//

#ifdef COOLING_THERMOSTAT_ACTIVE
#ifndef ARDUINOTHERMOSTAT_IR_SENDER_H
#define ARDUINOTHERMOSTAT_IR_SENDER_H
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Coolix.h>
#include "timer/Timer.h"
#include <algorithm>

#if !defined(COOLING_THERMOSTAT_CONTROL_PIN)
#error "Thermostat control pin should be set"
#endif

#if !defined(TIMER_ACTIVE)
#error "Thermostat require a timer"
#endif

#if !defined(TIME_SERVER)
#error "Thermostat require a a timer."
#endif
class CoolingThermostat{
private:
    IRCoolixAC *ac;
    float smoothed;
    float target;
    Timer *timer;
    time_t lastUpdate;
    bool state;
public:
    virtual ~CoolingThermostat();

    explicit CoolingThermostat(Timer *timer);

    void loop(float value);

    [[nodiscard]] float readValue() const;

    [[nodiscard]] bool shouldCool() const;

    void updateTargetTemperature(float temperature);
};

#endif //ARDUINOTHERMOSTAT_IR_SENDER_H
#endif //COOLING_THERMOSTAT_ACTIVE
