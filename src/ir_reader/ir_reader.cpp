//
// Created by matth on 2022-12-28.
//
#include "configuration.h"
#ifdef IR_READER
#include "ir_reader.h"

// Most of this is taken from IRRecvDumpV3 ino file.

IRrecv irrecv(IR_READER_PIN, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

void setupIrReader() {
    assert(irutils::lowLevelSanityCheck() == 0);
    irrecv.setUnknownThreshold(kMinUnknownSize);
    irrecv.setTolerance(kTolerancePercentage);  // Override the default tolerance.
    irrecv.enableIRIn();  // Start the receiver
}

void loopIrReader() {
    if (irrecv.decode(&results)) {
        // Display a crude timestamp.
        uint32_t now = millis();
        Serial.printf(D_STR_TIMESTAMP " : %06u.%03u\n", now / 1000, now % 1000);
        // Check if we got an IR message that was to big for our capture buffer.
        if (results.overflow) {
            Serial.printf(D_WARN_BUFFERFULL "\n", kCaptureBufferSize);
        }
        // Display the library version the message was captured with.
        Serial.println(D_STR_LIBRARY "   : v" _IRREMOTEESP8266_VERSION_STR "\n");
        // Display the tolerance percentage if it has been change from the default.
        if (kTolerancePercentage != kTolerance)
            Serial.printf(D_STR_TOLERANCE " : %d%%\n", kTolerancePercentage);
        // Display the basic output of what we found.
        Serial.print(resultToHumanReadableBasic(&results));
        // Display any extra A/C info if we have it.
        String description = IRAcUtils::resultAcToString(&results);
        if (description.length()) Serial.println(D_STR_MESGDESC ": " + description);
        yield();  // Feed the WDT as the text output can take a while to print.
        Serial.println(resultToSourceCode(&results));
        Serial.println();    // Blank line between entries
        yield();             // Feed the WDT (again)
    }
}

#endif //IR_READER