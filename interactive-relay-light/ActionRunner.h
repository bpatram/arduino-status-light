#ifndef action_runner_h
#define action_runner_h

#include "Action.h"

class ActionRunner {
public:
  Action** actions;
  int actionCount;
  int iterations;
  int pauseTime;

  ActionRunner();

  void setActions(Action*);
  void setActions(Action**, int);
  void setIterations(int);

  ~ActionRunner();

  void run();
};


#endif
