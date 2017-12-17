#ifndef constants_h
#define constants_h

#define DEBUG_OUT 1

enum Relay: int { ONE = 7, TWO = 6, THREE = 5, FOUR = 4, START = ONE, END = THREE, UNKNOWN = -1, ALL = -1, OFFSET = 4 };
enum Speed: int { INSTANT = 0, INSANE = 10, BLAZING = 50, FAST = 200, MEDIUM = 500, SLOW = 1000 };
enum Command: char {
  HELP = '?', STATUS = '!',
  ON = '+', OFF = '-', TOGGLE = '/',
  SEQUENCE = '~', FLASH = ':', DEMO = '%',
  RELAY_ONE = '1', RELAY_TWO = '2', RELAY_THREE = '3', RELAY_FOUR = '4'
};

#endif
