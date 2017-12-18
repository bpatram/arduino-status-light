#include <Arduino.h>
#include "Action.h"

Action::Action(Relay pin) {
  this->target = pin;
}

void Action::relayOff(Relay relay) {
  digitalWrite(getRelayPin(relay), LOW);
}

void Action::relayOn(Relay relay) {
  digitalWrite(getRelayPin(relay), HIGH);
}

void Action::relayInvert(Relay relay) {
  if (getRelayState(relay)) {
    relayOff(relay);
  } else {
    relayOn(relay);
  }
}

bool Action::getRelayState(Relay relay) {
  return digitalRead(getRelayPin(relay)) == HIGH;
}

int Action::getRelayPin(Relay relay) {
  switch (relay) {
    case Relay::Relay_ONE:
      return 7;
    case Relay::Relay_TWO:
      return 6;
    case Relay::Relay_THREE:
      return 5;
    case Relay::Relay_FOUR:
      return 4;
  }
  return 0;
}

void OnAction::run() {
  if (this->target == Relay::Relay_ALL) {
    Action::relayOn(Relay::Relay_ONE);
    Action::relayOn(Relay::Relay_TWO);
    Action::relayOn(Relay::Relay_THREE);
    Action::relayOn(Relay::Relay_FOUR);
  } else {
    Action::relayOn(this->target);
  }
}

void OffAction::run() {
  if (this->target == Relay::Relay_ALL) {
    Action::relayOff(Relay::Relay_ONE);
    Action::relayOff(Relay::Relay_TWO);
    Action::relayOff(Relay::Relay_THREE);
    Action::relayOff(Relay::Relay_FOUR);
  } else {
    Action::relayOff(this->target);
  }
}

void InvertAction::run() {
  if (this->target == Relay::Relay_ALL) {
    Action::relayInvert(Relay::Relay_ONE);
    Action::relayInvert(Relay::Relay_TWO);
    Action::relayInvert(Relay::Relay_THREE);
    Action::relayInvert(Relay::Relay_FOUR);
  } else {
    Action::relayInvert(this->target);
  }
}

void StatusAction::printStatus(Relay pin) {
  // TODO: use Serial.printf to clean up some of this formatting
  Serial.println(String(pin) + "\t" + (Action::getRelayState(pin) ? "ON" : "OFF"));
}

void StatusAction::run() {
  if (this->target == Relay::Relay_ALL) {
    printStatus(Relay::Relay_ONE);
    printStatus(Relay::Relay_TWO);
    printStatus(Relay::Relay_THREE);
    printStatus(Relay::Relay_FOUR);
  } else {
    printStatus(this->target);
  }
}

void HelpAction::run() {
  Serial.println("Here is a list of all possible commands:");
  Serial.println("\t ?                                        This help screen");
  Serial.println("\t !                                        Relay status (on or off)");
  Serial.println("\t +                                        Turn all relays on");
  Serial.println("\t -                                        Turn all relays off");
  Serial.println("\t /                                        Toggle all relays on or off");
  Serial.println("\t + relay                                  Turn a specific relay on");
  Serial.println("\t - relay                                  Turn a specific relay off");
  Serial.println("\t / relay                                  Toggle a specific relay on or off");
  Serial.println("\t : relay times onTime offTime             Flash all relays at once");
  Serial.println("\t ~ times onTime offTime pauseTime         Flash each relay in order");
}

void WaitAction::run() {
  if (this->pauseTime > 0) {
    delay(this->pauseTime);
  }
}
