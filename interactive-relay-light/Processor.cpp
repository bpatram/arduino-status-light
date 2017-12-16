#include "Processor.h"

Processor::Processor() { 
    this->relays = new Relay[0] {};
    this->relayCount = 0;
    this->loopCount = 1;
    this->eachAction = NULL;
    this->eachIteration = NULL;
  
    operationParameters defaultParams = { 500, 0, 0 };
    this->parameters = defaultParams;
  }
  
  Processor::Processor(eachAction_t eachFunc, iterationAction_t iterationFunc) : Processor::Processor() {
    this->relays = new Relay[4] { Relay::ONE, Relay::TWO, Relay::THREE, Relay::FOUR };
    this->relayCount = 4;
  
    this->eachAction = eachFunc;
    this->eachIteration = iterationFunc;
  } 
  
  Processor::Processor(Relay pin, eachAction_t eachFunc, iterationAction_t iterationFunc) : Processor::Processor(eachFunc, iterationFunc) { 
    this->relays = new Relay[1] { pin };
    this->relayCount = 1;
  }
  
  Processor::Processor(Relay* relays, int relaySize, eachAction_t eachFunc, iterationAction_t iterationFunc) : Processor::Processor(eachFunc, iterationFunc) {
    this->relays = relays;
    this->relayCount = relaySize;
  }
  
  Processor::~Processor() {
    delete[] this->relays;
  }
  
  void Processor::run() {
    for (int i = 0; i < this->loopCount; i++) {
      for(int j = 0; j < this->relayCount; j++) {
        if (this->eachAction != NULL) {
          this->eachAction(this->relays[j], this->parameters);
        }
        if (i+1 == this->loopCount) {
          delay(this->parameters.offTime);
        }
      }
      if (this->eachIteration != NULL) {
        this->eachIteration(this);
      }
      if (i+1 == this->loopCount) {
        // TODO: figure out good way to not block input and implement ability to abort
        delay(this->parameters.pauseTime);
      }
    }
  }