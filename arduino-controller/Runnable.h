#ifndef runnable_h
#define runnable_h

class Runnable {
public:
  Runnable() {}
  virtual ~Runnable() {}

  virtual void run()=0;
};

#endif
