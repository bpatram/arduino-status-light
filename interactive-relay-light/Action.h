#ifndef action_h
#define action_h

#include "constants.h"

class Action {
public:
  Relay target;

  Action(Relay);

  virtual void run();

  static void relayOn(Relay);
  static void relayOff(Relay);
  static void relayInvert(Relay);
  static bool getRelayState(Relay);
  static int getRelayIndex(Relay);
};

class OnAction : public Action {
public:
  OnAction(Relay r) : Action(r) {}
  virtual void run();
};

class OffAction : public Action {
public:
  OffAction(Relay r) : Action(r) {}
  virtual void run();
};

class InvertAction : public Action {
public:
  InvertAction(Relay r) : Action(r) {}
  virtual void run();
};

class StatusAction : public Action {
public:
  StatusAction(Relay r) : Action(r) {}
  virtual void run();

  void printStatus(Relay);
};

class HelpAction : public Action {
public:
  HelpAction() : Action(Relay::UNKNOWN) {}
  virtual void run();
};

class WaitAction : public Action {
public:
  int pauseTime;
  WaitAction(int pauseTime) : Action(Relay::UNKNOWN) {
    this->pauseTime = pauseTime;
  }
  virtual void run();
};

#endif
