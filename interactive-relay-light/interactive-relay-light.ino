#include <Arduino.h>

#include "Processor.h"
#include "Actions.h"
#include "Operations.h"
#include "constants.h"

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

namespace Operation {
  void allOn() {
    ::Processor op(&Action::relayOn);
    op.run();
  }

  void allOff() {
    ::Processor op(&Action::relayOff);
    op.run();
  }

  void allToggle() {
    ::Processor op(&Action::relayToggle);
    op.run();
  }

  void allStatus() {
    ::Processor op(&Action::printStatus);
    op.run();
  }

  void oneOn(Relay pin) {
    ::Processor op(pin, &Action::relayOn);
    op.run();
  }

  void oneOff(Relay pin) {
    ::Processor op(pin, &Action::relayOff);
    op.run();
  }

  void oneToggle(Relay pin) {
    ::Processor op(pin, &Action::relayToggle);
    op.run();
  }

  void printHelp() {
    ::Processor op(Relay::ONE, &Action::printHelp);
    op.run();
  }

  void sequenceFlash(int iterations = 3, int onDuration = Speed::SLOW, int offDuration = Speed::SLOW, int pauseDuration = Speed::SLOW) {
    operationParameters defaultParams = { onDuration, offDuration, pauseDuration };
    ::Processor op(&Action::flash);
    op.parameters = defaultParams;
    op.loopCount = iterations;
    op.run();
  }

  void allFlash(int iterations = 3, int onDuration = Speed::SLOW, int offDuration = Speed::SLOW, int pauseDuration = Speed::SLOW) {
    operationParameters defaultParams = { onDuration, offDuration, pauseDuration };
    ::Processor op(&Action::relayOn, &Action::allOff);
    op.parameters = defaultParams;
    op.loopCount = iterations;
    op.run();
  }

  void allOff(Processor* proc) {
    Operation::allOff();
  }

  void allOn(Processor* proc) {
    Operation::allOn();
  }

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

  Operation::allStatus();
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
//int inputParameterLength[maxParams];

int processParameters(char* input, int size) {
  // empty buffer (from previous run)
  memset(inputParameters, '\0', sizeof(char) * maxParamLength * maxParams);

  char* parameters = strtok(input, " "); // break string up into parts by space, returns first part

  int i = 0;
  while (parameters != NULL && i < maxParams) {
    strncpy(inputParameters[i], parameters, maxParamLength); // copy char array into param array
    Serial.println(parameters);
    parameters = strtok(NULL, " "); // passing NULL will make strtok use last string
    i++;
  }

  return i; // returns param count
}

void loop() {
  if (Serial.available() > 0) {
    Serial.readBytes(serialBuffer, bufferLength); // read data into serialBuffer
    int paramCount = processParameters(serialBuffer, bufferLength); // setup params into inputParameters
    if (paramCount > 0) {
      processCommand(inputParameters, paramCount);
    }
  }
}

void processCommand(char input[][maxParamLength], int paramCount) {
  Serial.println("Received " + String(paramCount) + " parameters: ");
  for (int i = 0; i < paramCount; i++) {
    Serial.println("[" + String(i) + "] = " + input[i]);
  }

  switch (input[0][0]) {

    case Command::STATUS:
      Operation::allStatus();
    break;

    case Command::HELP:
      Operation::printHelp();
    break;

    case Command::ON: { // command, relauy
      Relay target = intToRelay(charToInt(input[1][0]));
      if (target == Relay::UNKNOWN) {
        Operation::allOn();
      } else {
        Serial.println(target);
        Operation::oneOn(target);
      }
      Operation::allStatus();
    } break;

    case Command::OFF: { // command, relay
      Relay target = intToRelay(charToInt(input[1][0]));
      if (target == Relay::UNKNOWN) {
        Operation::allOff();
      } else {
        Operation::oneOff(target);
      }
      Operation::allStatus();
    } break;

    case Command::TOGGLE: { // command, relay
      Relay target = intToRelay(charToInt(input[1][0]));
      if (target == Relay::UNKNOWN) {
        Operation::allToggle();
      } else {
        Operation::oneToggle(target);
      }
      Operation::allStatus();
    } break;

    case Command::SEQUENCE: { // command, flashCount, onDur, offDur, pauseDur
      Operation::allOff(); // shut off all lights to start clean

      int flashCount = paramCount > 1 ? atoi(input[1]) : 1;
      int onDuration = paramCount > 2 ? atoi(input[2]) : Speed::FAST;
      int offDuration = paramCount > 3 ? atoi(input[3]) : Speed::INSTANT;
      int pauseDuration = paramCount > 4 ? atoi(input[4]) : Speed::INSTANT;

      Operation::sequenceFlash(flashCount, onDuration, offDuration, pauseDuration);
      Operation::allStatus();
    } break;

    case Command::ALL_FLASH: { // command, flashCount, onDur, offDur, pauseDur
      int flashCount = paramCount > 1 ? atoi(input[1]) : 1;
      int onDuration = paramCount > 2 ? atoi(input[2]) : Speed::MEDIUM;
      int offDuration = paramCount > 3 ? atoi(input[3]) : Speed::MEDIUM;
      int pauseDuration = paramCount > 4 ? atoi(input[4]) : Speed::INSTANT;

      Operation::allFlash(flashCount, onDuration, offDuration, pauseDuration);
      Operation::allStatus();
    } break;

    case Command::SINGLE_FLASH: { // command, relay, flashCount, onDur, offDur, pauseDur
      Relay target = paramCount > 1 ? intToRelay(charToInt(input[1][0])) : Relay::UNKNOWN;
      int flashCount = paramCount > 2 ? atoi(input[2]) : 1;
      int onDuration = paramCount > 3 ? atoi(input[3]) : Speed::MEDIUM;
      int offDuration = paramCount > 4 ? atoi(input[4]) : Speed::MEDIUM;
      int pauseDuration = paramCount > 5 ? atoi(input[5]) : Speed::INSTANT;

      if (target != Relay::UNKNOWN) {
        // loopFlash(target, flashCount, onDuration, offDuration, pauseDuration);
      }
      Operation::allStatus();
    } break;

    case Command::DEMO:
      runDemo();
    break;
  }
}




