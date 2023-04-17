//
// Created by matth on 2023-01-02.
//

#ifdef IR_SENDER
#ifndef ARDUINOTHERMOSTAT_IR_SENDER_H
#define ARDUINOTHERMOSTAT_IR_SENDER_H
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Coolix.h>

extern IRCoolixAC ac;  // Set the GPIO to be used for sending messages.

#ifdef DEBUG_SERIAL
void debugAc();
#endif //DEBUG_SERIAL

void setupIrSender();

void loopIrSender();

#endif //ARDUINOTHERMOSTAT_IR_SENDER_H
#endif //IR_SENDER
