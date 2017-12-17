#include <Arduino.h>

#include "constants.h"
#include "Action.h"
#include "ActionRunner.h"

#define bufferLength 16
#define maxParamLength 4
#define maxParams 6

int charToInt(char c) {
  // we assume ASCII
  return c - '0';
}

Relay intToRelay(int value) {
  switch (value) {
    case 1:
      return Relay::ONE;
    case 2:
      return Relay::TWO;
    case 3:
      return Relay::THREE;
    case 4:
      return Relay::FOUR;
  }
  return Relay::UNKNOWN;
}

void setup() {
  Serial.begin(19200);

  Serial.println("-- Light Relay System --");
  Serial.print("Initializing... ");

  pinMode(Relay::ONE, OUTPUT);
  pinMode(Relay::TWO, OUTPUT);
  pinMode(Relay::THREE, OUTPUT);
  pinMode(Relay::FOUR, OUTPUT);

  Serial.println("Ready!");

  ::StatusAction act(Relay::ALL);
  act.run();
}

void runDemo() {
  Serial.println("Test: All on");
  // allOn();
  delay(1000);
  Serial.println("Test: All off");
  // allOff();
  delay(1000);
  Serial.println("Test: Toggle all test with 1, 2 on");
  // relayOn(Relay::ONE);
  // relayOn(Relay::TWO);
  // allToggle();
  delay(200);
  // allToggle();
  delay(1000);
  Serial.println("Test: Looping flash");
  // allOff();
  // loopFlash(Relay::ONE, 3, Speed::FAST, Speed::FAST, Speed::INSTANT);
  // loopFlash(Relay::TWO, 3, Speed::FAST, Speed::FAST, Speed::INSTANT);
  // loopFlash(Relay::THREE, 3, Speed::FAST, Speed::FAST, Speed::INSTANT);
  // loopFlash(Relay::FOUR, 3, Speed::FAST, Speed::FAST, Speed::INSTANT);
  delay(1000);
  Serial.println("Test: Sequence");
  // sequenceFlash(3, Speed::FAST, Speed::INSTANT, Speed::INSTANT);
  delay(1000);
  Serial.println("Test: All flash");
  // allFlash(3, Speed::MEDIUM, Speed::MEDIUM);
  delay(1000);
  Serial.println("Test: Speed flash");
  // loopFlash(Relay::ONE, 3, 100, 100, Speed::INSTANT);
  // loopFlash(Relay::TWO, 5, 50, 50, Speed::INSTANT);
  // loopFlash(Relay::THREE, 10, 20, 20, Speed::INSTANT);
  // loopFlash(Relay::FOUR, 10, 50, 10, Speed::INSTANT);
}

char serialBuffer[bufferLength];
char inputParameters[maxParams][maxParamLength];

int processParameters(char* input, int size) {
  // empty buffer (from previous run)
  memset(inputParameters, '\0', sizeof(char) * maxParamLength * maxParams);

  char* parameters = strtok(input, " "); // break string up into parts by space, returns first part

  int i = 0;
  while (parameters != NULL && i < maxParams) {
    strncpy(inputParameters[i], parameters, maxParamLength); // copy char array into param array
    parameters = strtok(NULL, " "); // passing NULL will make strtok use last string
    i++;
  }

  return i; // returns param count
}

void loop() {
  if (Serial.available() > 0) {
    Serial.readBytes(serialBuffer, bufferLength); // read data into serialBuffer
    int paramCount = processParameters(serialBuffer, bufferLength); // setup params into inputParameters
    if (paramCount > 0) { // only process if a command was sent (which is the first string in the array)
      processCommand(inputParameters, paramCount);
    }
  }
}

void processCommand(char input[][maxParamLength], int paramCount) {
  #if DEBUG_OUT == 1
  Serial.println("Received " + String(paramCount) + " parameters: ");
  for (int i = 0; i < paramCount; i++) {
    Serial.println("[" + String(i) + "] = " + input[i]);
  }
  #endif

  ActionRunner runner;

  switch (input[0][0]) {

    case Command::HELP: {
      runner.setActions(new HelpAction());
    } break;

    case Command::ON: { // command, relay
      Relay target = intToRelay(charToInt(input[1][0]));
      runner.setActions(new OnAction(target));
    } break;

    case Command::OFF: { // command, relay
      Relay target = intToRelay(charToInt(input[1][0]));
      runner.setActions(new OffAction(target));
    } break;

    case Command::TOGGLE: { // command, relay
      Relay target = intToRelay(charToInt(input[1][0]));
      runner.setActions(new InvertAction(target));
    } break;

    case Command::SEQUENCE: { // command, flashCount, onDur, offDur, pauseDur
      int flashCount = paramCount > 1 ? atoi(input[1]) : 1;
      int onDuration = paramCount > 2 ? atoi(input[2]) : Speed::FAST;
      int offDuration = paramCount > 3 ? atoi(input[3]) : Speed::INSTANT;
      int pauseDuration = paramCount > 4 ? atoi(input[4]) : Speed::INSTANT;

      runner.setActions(new Action*[16] {
        new InvertAction(Relay::ONE),
        new WaitAction(onDuration),
        new InvertAction(Relay::ONE),
        new WaitAction(offDuration),

        new InvertAction(Relay::TWO),
        new WaitAction(onDuration),
        new InvertAction(Relay::TWO),
        new WaitAction(offDuration),

        new InvertAction(Relay::THREE),
        new WaitAction(onDuration),
        new InvertAction(Relay::THREE),
        new WaitAction(offDuration),

        new InvertAction(Relay::FOUR),
        new WaitAction(onDuration),
        new InvertAction(Relay::FOUR),
        new WaitAction(offDuration)
      }, 16);

      runner.iterations = flashCount;
      runner.pauseTime = pauseDuration;
    } break;

    case Command::FLASH: { // command, relay, flashCount, onDur, offDur, pauseDur
      Relay target = paramCount > 1 ? intToRelay(charToInt(input[1][0])) : Relay::ALL;
      int flashCount = paramCount > 2 ? atoi(input[2]) : 1;
      int onDuration = paramCount > 3 ? atoi(input[3]) : Speed::MEDIUM;
      int offDuration = paramCount > 4 ? atoi(input[4]) : Speed::MEDIUM;
      int pauseDuration = paramCount > 5 ? atoi(input[5]) : Speed::INSTANT;

      runner.setActions(new Action*[4] {
        new InvertAction(target),
        new WaitAction(onDuration),
        new InvertAction(target),
        new WaitAction(offDuration)
      }, 4);

      runner.iterations = flashCount;
      runner.pauseTime = pauseDuration;
    } break;

    case Command::DEMO: {
      runDemo();
    } break;
  }

  runner.run();

  ::StatusAction act(Relay::ALL);
  act.run();
}
