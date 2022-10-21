#include "configuration.h"

#ifdef THERMOSTAT_ACTIVE
#include "thermostat.h"
#include <algorithm>

Thermostat::Thermostat(Timer *timer) {
    pinMode(THERMOSTAT_CONTROL_PIN, OUTPUT);
    this->smoothed = INITIAL_VALUE;
    this->timer = timer;
    this->lastUpdate = 0;
    this->target = DEFAULT_TARGET;
    this->state = false;
}

Thermostat::~Thermostat() {
    delete this->timer;
    this->timer = nullptr;
}

void Thermostat::loop(float value) {
    //update value
    if (this->lastUpdate + UPDATE_DELAY < timer->n()) {
        if (this->smoothed != -1) {
            this->smoothed = ALPHA * value + (1 - ALPHA) * this->smoothed;
        } else {
            this->smoothed = value;
        }
        this->lastUpdate = timer->n();
    }
    LOG_IF_DEBUG_LN("Updated Thermostat value to:")
    LOG_IF_DEBUG_LN(this->readValue())
    //update state
    if (state) { //already heating
        if (value > this->target + HYSTERESIS_DELTA) {
            // if we went over the hysteresis, turn it off
            this->state = false;
        } //else continue heating
    } else {
        //if we went below hysteresis, start heating
        if (value < this->target - HYSTERESIS_DELTA) {
            this->state = true;
        } //else keep it off
    }
    //update the pin
    digitalWrite(THERMOSTAT_CONTROL_PIN, this->state ? HIGH : LOW);
    LOG_IF_DEBUG_LN("Updated Thermostat value and pin to:")
    LOG_IF_DEBUG_LN(this->shouldHeat())
}

float Thermostat::readValue() const {
    return this->smoothed;
}

bool Thermostat::shouldHeat() const {
    return this->state;
}

void Thermostat::updateTargetTemperature(float temperature) {
    this->target = MAX(temperature, DEFAULT_TARGET);
}

#endif //THERMOSTAT_ACTIVE