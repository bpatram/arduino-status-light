#ifndef processor_h
#define processor_h

#include <Arduino.h>
#include "constants.h"

struct operationParameters {
  int onTime;
  int offTime;
  int pauseTime;
};

class Processor {

public:
  typedef void (*eachAction_t)(Relay, operationParameters);
  typedef void (*iterationAction_t)(Processor*);

  Relay* relays;
  int relayCount;
  int loopCount;
  operationParameters parameters;
  eachAction_t eachAction;
  iterationAction_t eachIteration;

  Processor(Relay*, int, eachAction_t, iterationAction_t  = NULL);
  Processor(Relay, eachAction_t, iterationAction_t  = NULL);
  Processor(eachAction_t, iterationAction_t  = NULL);
  Processor();
  ~Processor();

  void run();
};

#endif
