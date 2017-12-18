#ifndef constants_h
#define constants_h

#define DEBUG_OUT 1

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
