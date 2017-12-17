#include <Arduino.h>
#include "Action.h"

Action::Action(Relay pin) {
  this->target = pin;
}

void Action::run() {}

void Action::relayOff(Relay pin) {
  digitalWrite(pin, LOW);
}

void Action::relayOn(Relay pin) {
  digitalWrite(pin, HIGH);
}

void Action::relayInvert(Relay pin) {
  if (getRelayState(pin)) {
    relayOff(pin);
  } else {
    relayOn(pin);
  }
}

bool Action::getRelayState(Relay pin) {
  return digitalRead(pin) == HIGH;
}

int Action::getRelayIndex(Relay pin) {
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

void OnAction::run() {
  if (this->target == Relay::ALL) {
    Action::relayOn(Relay::ONE);
    Action::relayOn(Relay::TWO);
    Action::relayOn(Relay::THREE);
    Action::relayOn(Relay::FOUR);
  } else {
    Action::relayOn(this->target);
  }
}

void OffAction::run() {
  if (this->target == Relay::ALL) {
    Action::relayOff(Relay::ONE);
    Action::relayOff(Relay::TWO);
    Action::relayOff(Relay::THREE);
    Action::relayOff(Relay::FOUR);
  } else {
    Action::relayOff(this->target);
  }
}

void InvertAction::run() {
  if (this->target == Relay::ALL) {
    Action::relayInvert(Relay::ONE);
    Action::relayInvert(Relay::TWO);
    Action::relayInvert(Relay::THREE);
    Action::relayInvert(Relay::FOUR);
  } else {
    Action::relayInvert(this->target);
  }
}

void StatusAction::printStatus(Relay pin) {
  // TODO: use Serial.printf to clean up some of this formatting
  Serial.println(String(Action::getRelayIndex(pin)) + "\t" + (Action::getRelayState(pin) ? "ON" : "OFF"));
}

void StatusAction::run() {
  if (this->target == Relay::ALL) {
    printStatus(Relay::ONE);
    printStatus(Relay::TWO);
    printStatus(Relay::THREE);
    printStatus(Relay::FOUR);
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
