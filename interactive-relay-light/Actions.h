#ifndef actions_h
#define actions_h

#include <Arduino.h>
#include "constants.h"
#include "Processor.h"

bool getRelayState(Relay pin);
int relayToInt(Relay pin);

namespace Action {
    void relayOn(Relay pin, operationParameters params);
    void relayOff(Relay pin, operationParameters params);
    void relayToggle(Relay pin, operationParameters params);
    void flash(Relay pin, operationParameters params);
    void printStatus(Relay pin, operationParameters params);
    void printHelp(Relay pin, operationParameters params);

    void allOff(Processor* proc);
    void allOn(Processor* proc);
}

#endif