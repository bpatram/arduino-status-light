#ifndef action_runner_h
#define action_runner_h

#include "Runnable.h"
#include "Action.h"

class ActionRunner : public Runnable {
public:
  Runnable** actions;
  int actionCount;
  int iterations;
  int pauseTime;

  ActionRunner();
  ~ActionRunner();

  virtual void setActions(Runnable*);
  virtual void setActions(Runnable**, int);

  virtual void run();
};

#endif
