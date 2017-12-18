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
  if (getRelayState(relay) == StatusResponse_State::StatusResponse_State_ON) {
    relayOff(relay);
  } else {
    relayOn(relay);
  }
}

StatusResponse_State Action::getRelayState(Relay relay) {
  if (digitalRead(getRelayPin(relay)) == HIGH) {
    return StatusResponse_State::StatusResponse_State_ON;
  }
  return StatusResponse_State::StatusResponse_State_OFF;
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

void StatusAction::run() {
  StatusResponse_Status relayOne = { Relay::Relay_ONE, Action::getRelayState(Relay::Relay_ONE) };
  StatusResponse_Status relayTwo = { Relay::Relay_TWO, Action::getRelayState(Relay::Relay_TWO) };
  StatusResponse_Status relayThree = { Relay::Relay_THREE, Action::getRelayState(Relay::Relay_THREE) };
  StatusResponse_Status relayFour = { Relay::Relay_FOUR, Action::getRelayState(Relay::Relay_FOUR) };
  // StatusResponse_Status statuses[4] = { relayOne, relayTwo, relayThree, relayFour };

  StatusResponse message = { relayOne, relayTwo, relayThree, relayFour };

  if (!pb_encode(this->stream, StatusResponse_fields, &message)) {
    Serial.println(PB_GET_ERROR(this->stream));
  }
}

void WaitAction::run() {
  if (this->pauseTime > 0) {
    delay(this->pauseTime);
  }
}
