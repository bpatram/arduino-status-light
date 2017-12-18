#ifndef constants_h
#define constants_h

#define DEBUG_OUT 1

enum Speed: int { INSTANT = 0, INSANE = 10, BLAZING = 50, FAST = 200, MEDIUM = 500, SLOW = 1000 };
enum Command: char {
  HELP = '?',
  STATUS = '!',
  ON = '+',
  OFF = '-',
  TOGGLE = '/',
  SEQUENCE = '~',
  FLASH = ':',
  DEMO = '%'
};

#endif
