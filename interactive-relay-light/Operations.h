#ifndef operations_h
#define operations_h

#include "constants.h"

namespace Operation {
  void allOn();
  void allOff();
  void allToggle();
  void allStatus();
  void oneOn(Relay pin);
  void oneOff(Relay pin);
  void oneToggle(Relay pin);
  void printHelp();
  void sequenceFlash(int iterations = 3, int onDuration = Speed::SLOW, int offDuration = Speed::SLOW, int pauseDuration = Speed::SLOW);
  void allFlash(int iterations = 3, int onDuration = Speed::SLOW, int offDuration = Speed::SLOW, int pauseDuration = Speed::SLOW);
}

#endif
