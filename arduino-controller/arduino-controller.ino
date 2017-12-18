#include <Arduino.h>

#include <pb_arduino.h>
#include <pb_common.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <pb.h>

#include "commands.pb.h"

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
      return Relay::Relay_ONE;
    case 2:
      return Relay::Relay_TWO;
    case 3:
      return Relay::Relay_THREE;
    case 4:
      return Relay::Relay_FOUR;
  }
  return Relay::Relay_ALL;
}

void setup() {
  Serial.begin(19200);

  Serial.println("-- Light Relay System --");
  Serial.print("Initializing... ");

  pinMode(Action::getRelayPin(Relay::Relay_ONE), OUTPUT);
  pinMode(Action::getRelayPin(Relay::Relay_TWO), OUTPUT);
  pinMode(Action::getRelayPin(Relay::Relay_THREE), OUTPUT);
  pinMode(Action::getRelayPin(Relay::Relay_FOUR), OUTPUT);

  Serial.println("Ready!");

  ::StatusAction act(Relay::Relay_ALL);
  act.run();
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

      setupSequenceRunner(&runner, flashCount, onDuration, offDuration, pauseDuration);
    } break;

    case Command::FLASH: { // command, relay, flashCount, onDur, offDur, pauseDur
      Relay target = paramCount > 1 ? intToRelay(charToInt(input[1][0])) : Relay::Relay_ALL;
      int flashCount = paramCount > 2 ? atoi(input[2]) : 1;
      int onDuration = paramCount > 3 ? atoi(input[3]) : Speed::MEDIUM;
      int offDuration = paramCount > 4 ? atoi(input[4]) : Speed::MEDIUM;
      int pauseDuration = paramCount > 5 ? atoi(input[5]) : Speed::INSTANT;

      setupFlashRunner(&runner, target, flashCount, onDuration, offDuration, pauseDuration);
    } break;

    case Command::DEMO: {

      setupDemoRunner(&runner);
    } break;
  }

  runner.run();

  ::StatusAction act(Relay::Relay_ALL);
  act.run();
}

void setupFlashRunner(ActionRunner* runner, Relay target, int flashCount, int onDuration, int offDuration, int pauseDuration) {
  runner->setActions(new Action*[4] {
    new InvertAction(target),
    new WaitAction(onDuration),
    new InvertAction(target),
    new WaitAction(offDuration)
  }, 4);

  runner->iterations = flashCount;
  runner->pauseTime = pauseDuration;
}

void setupSequenceRunner(ActionRunner* runner, int flashCount, int onDuration, int offDuration, int pauseDuration) {
  runner->setActions(new Action*[16] {
    new InvertAction(Relay::Relay_ONE),
    new WaitAction(onDuration),
    new InvertAction(Relay::Relay_ONE),
    new WaitAction(offDuration),

    new InvertAction(Relay::Relay_TWO),
    new WaitAction(onDuration),
    new InvertAction(Relay::Relay_TWO),
    new WaitAction(offDuration),

    new InvertAction(Relay::Relay_THREE),
    new WaitAction(onDuration),
    new InvertAction(Relay::Relay_THREE),
    new WaitAction(offDuration),

    new InvertAction(Relay::Relay_FOUR),
    new WaitAction(onDuration),
    new InvertAction(Relay::Relay_FOUR),
    new WaitAction(offDuration)
  }, 16);

  runner->iterations = flashCount;
  runner->pauseTime = pauseDuration;
}

void setupDemoRunner(ActionRunner* runner) {
  ActionRunner* oneFlashRunner = new ActionRunner();
  setupFlashRunner(oneFlashRunner, Relay::Relay_ONE, 3, Speed::FAST, Speed::FAST, Speed::INSTANT);

  ActionRunner* twoFlashRunner = new ActionRunner();
  setupFlashRunner(twoFlashRunner, Relay::Relay_TWO, 3, Speed::FAST, Speed::FAST, Speed::INSTANT);

  ActionRunner* threeFlashRunner = new ActionRunner();
  setupFlashRunner(threeFlashRunner, Relay::Relay_THREE, 3, Speed::FAST, Speed::FAST, Speed::INSTANT);

  ActionRunner* fourFlashRunner = new ActionRunner();
  setupFlashRunner(fourFlashRunner, Relay::Relay_FOUR, 3, Speed::FAST, Speed::FAST, Speed::INSTANT);

  ActionRunner* sequenceRunner = new ActionRunner();
  setupSequenceRunner(sequenceRunner, 3, Speed::FAST, Speed::INSTANT, Speed::INSTANT);

  ActionRunner* allFlashRunner = new ActionRunner();
  setupFlashRunner(allFlashRunner, Relay::Relay_ALL, 3, Speed::MEDIUM, Speed::MEDIUM, Speed::INSTANT);

  ActionRunner* allFlashRunner1 = new ActionRunner();
  setupFlashRunner(allFlashRunner1, Relay::Relay_ONE, 5, Speed::FAST, Speed::FAST, Speed::INSTANT);

  ActionRunner* allFlashRunner2 = new ActionRunner();
  setupFlashRunner(allFlashRunner2, Relay::Relay_TWO, 10, Speed::BLAZING, Speed::BLAZING, Speed::INSTANT);

  ActionRunner* allFlashRunner3 = new ActionRunner();
  setupFlashRunner(allFlashRunner3, Relay::Relay_THREE, 20, Speed::INSANE, Speed::INSANE, Speed::INSTANT);

  runner->setActions(new Runnable*[24] {
    // []
    new OffAction(Relay::Relay_ALL), // reset all light states

    // [1,2,3,4] -200-> [] x3
    allFlashRunner,

    new WaitAction(1000),

    new OffAction(Relay::Relay_ALL),
    oneFlashRunner,
    twoFlashRunner,
    threeFlashRunner,
    fourFlashRunner,

    new WaitAction(1000),

    // [1,3] -200-> [2,4] -200> [1,3] -200-> [2,4]
    new OnAction(Relay::Relay_ONE),
    new OnAction(Relay::Relay_THREE),
    new WaitAction(200),
    new InvertAction(Relay::Relay_ALL),
    new WaitAction(200),
    new InvertAction(Relay::Relay_ALL),
    new WaitAction(200),
    new InvertAction(Relay::Relay_ALL),
    new OffAction(Relay::Relay_ALL),

    new WaitAction(1000),

    // [] -> [1] -> [2] -> [3] -> [4] -> [] x3
    sequenceRunner,

    new WaitAction(1000),

    allFlashRunner1,
    allFlashRunner2,
    allFlashRunner3
  }, 24);
}
