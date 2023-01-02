//
// Created by matth on 2022-12-28.
//
#include "configuration.h"
#ifdef IR_READER
#ifndef ARDUINOTHERMOSTAT_IR_READER_H
#define ARDUINOTHERMOSTAT_IR_READER_H
#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
//#include <IRremote.hpp>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>

const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 90;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance;  // kTolerance is normally 25%

void setupIrReader();

void loopIrReader();

#endif //ARDUINOTHERMOSTAT_IR_READER_H
#endif //IR_READER