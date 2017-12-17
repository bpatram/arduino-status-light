#include <Arduino.h>
#include "ActionRunner.h"

ActionRunner::ActionRunner() {
  this->actions = new Action*[0] {};
  this->actionCount = 0;
  this->iterations = 1;
  this->pauseTime = 0;
}

void ActionRunner::setActions(Runnable** actions, int size) {
  this->actions = actions;
  this->actionCount = size;
}

void ActionRunner::setActions(Runnable* action) {
  this->setActions(new Action*[1] { action }, 1);
}

ActionRunner::~ActionRunner() {
  for(int i = 0; i < this->actionCount; i++) {
    delete this->actions[i];
  }
  delete[] this->actions;
}

void ActionRunner::run() {
  for (int i = 0; i < this->iterations; i++) {
    for(int j = 0; j < this->actionCount; j++) {
      if (this->actions[j] != NULL) {
        this->actions[j]->run();
      }
      if (j < this->actionCount && i < this->iterations && this->pauseTime > 0) {
        delay(this->pauseTime);
      }
    }
  }
}
