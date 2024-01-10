//
// Created by matth on 2023-01-02.
//

#ifdef HEATING_THERMOSTAT_ACTIVE
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Coolix.h>
#include "timer/Timer.h"
#include <algorithm>

#if !defined(HEATING_THERMOSTAT_CONTROL_PIN)
#error "Thermostat control pin should be set"
#endif

#if !defined(TIMER_ACTIVE)
#error "Thermostat require a timer"
#endif

#if !defined(TIME_SERVER)
#error "Thermostat require a a timer."
#endif
class AcHeatingThermostat{
private:
    IRCoolixAC *ac;
    float smoothed;
    float target;
    bool shouldUpdate;
    Timer *timer;
    time_t lastUpdate;
    bool isHeating;
public:
    virtual ~AcHeatingThermostat();

    explicit AcHeatingThermostat(Timer *timer);

    void loop(float value);

    [[nodiscard]] float readValue() const;
    [[nodiscard]] float readTarget() const;

    void updateTargetTemperature(float temperature);
};

#endif //HEATING_THERMOSTAT_ACTIVE
