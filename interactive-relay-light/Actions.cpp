#include <Arduino.h>

#include "Actions.h"
#include "constants.h"
#include "Operations.h"

bool getRelayState(Relay pin) {
  return digitalRead(pin) == HIGH;
}

int relayToInt(Relay pin) {
  switch (pin) {
    case Relay::ONE:
      return 1;
    case Relay::TWO:
      return 2;
    case Relay::THREE:
      return 3;
    case Relay::FOUR:
      return 4;
  }
  return -1;
}

namespace Action {

  void relayOn(Relay pin, operationParameters params) {
    digitalWrite(pin, HIGH);
  }
      
  void relayOff(Relay pin, operationParameters params) {
    digitalWrite(pin, LOW);
  }
      
  void relayToggle(Relay pin, operationParameters params) {
    if (getRelayState(pin)) {
      relayOff(pin, params);
    } else {
      relayOn(pin, params);
    }
  }

  void flash(Relay pin, operationParameters params) {
    relayOn(pin, params);
    delay(params.onTime);
    relayOff(pin, params);
  }

  void printStatus(Relay pin, operationParameters params) {
    // TODO: use Serial.printf to clean up some of this formatting
    Serial.println(String(relayToInt(pin)) + "\t" + (getRelayState(pin) ? "ON" : "OFF"));
  }

  void printHelp(Relay pin, operationParameters params) {
    Serial.println("Here is a list of all possible commands:");
    Serial.println("\t ?                                        This help screen");
    Serial.println("\t !                                        Relay status (on or off)");
    Serial.println("\t +                                        Turn all relays on");
    Serial.println("\t -                                        Turn all relays off");
    Serial.println("\t /                                        Toggle all relays on or off");
    Serial.println("\t + relay                                  Turn a specific relay on");
    Serial.println("\t - relay                                  Turn a specific relay off");
    Serial.println("\t / relay                                  Toggle a specific relay on or off");
    Serial.println("\t . relay times onTime offTime pauseTime   Flash a specific relay");
    Serial.println("\t : times onTime offTime                   Flash all relays at once");
    Serial.println("\t ~ times onTime offTime pauseTime         Flash each relay in order");
  }

  void allOff(Processor* proc) {
    Operation::allOff();
  }

  void allOn(Processor* proc) {
    Operation::allOn();
  }
}
