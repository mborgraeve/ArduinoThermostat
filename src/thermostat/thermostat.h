#include "configuration.h"

#ifdef THERMOSTAT_ACTIVE
#include "timer/Timer.h"
#include <algorithm>
#if !defined(THERMOSTAT_CONTROL_PIN)

#error "Thermostat control pin should be set"
#endif

#if !defined(TIME_SERVER)
#error "Thermostat require a a timer."
#endif

#ifndef ARDUINOTHERMOSTAT_THERMOSTAT_H
#define ARDUINOTHERMOSTAT_THERMOSTAT_H

class Thermostat {
private:
    float smoothed;
    float target;
    Timer *timer;
    time_t lastUpdate;
    bool state;
public:
    virtual ~Thermostat();

    explicit Thermostat(Timer *timer);

    void loop(float value);

    [[nodiscard]] float readValue() const;

    [[nodiscard]] bool shouldHeat() const;

    void updateTargetTemperature(float temperature);
};

#endif //ARDUINOTHERMOSTAT_THERMOSTAT_H
#endif //THERMOSTAT_ACTIVE
