//// Created by matth on 2023-01-02.
//

#include "configuration.h"

#ifdef IR_SENDER
#include "ir_sender.h"

IRCoolixAC ac(IR_SENDER_PIN);

boolean state = false;
int tempState = 0;
boolean tempUp = false;


#ifdef DEBUG_SERIAL

void debugAc() {
    Serial.println("Toshiba A/C remote is in the following state:");
    Serial.printf("  %s\n", ac.toString().c_str());
    // Display the encoded IR sequence.
    unsigned int ir_code = ac.getRaw();
    Serial.print("IR Code: 0x");
    Serial.printf("%02X", ir_code);
    Serial.println();
}

#endif //DEBUG_SERIAL

void setupIrSender() {
    ac.begin();
    ac.on();
    #ifdef DEBUG_SERIAL
    debugAc();
    #endif //DEBUG_SERIAL
}

void loopIrSender() {
    ac.setMode(kCoolixHeat);
    ac.setFan(kCoolixFanAuto);
    if (state) {
        ac.on();
        ac.setTemp(19 + tempState);
        state = !state;
        if (tempUp) {
            tempState += 1;
            if (tempState > 22) { tempUp = false; }
        } else {
            tempState -= 1;
            if (tempState < 19) { tempUp = true; }
        }
    } else {
        ac.off();
        state = !state;
    }

    ac.send();
    #ifdef DEBUG_SERIAL
    debugAc();
    #endif //DEBUG_SERIAL
}

#endif //IR_SENDER