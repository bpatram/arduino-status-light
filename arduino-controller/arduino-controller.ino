#include <Arduino.h>

#include <pb_arduino.h>
#include <pb_common.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <pb.h>

#include "commands.pb.h"

#include "constants.h"
#include "Runnable.h"
#include "Action.h"
#include "ActionRunner.h"

enum Speed: int { INSTANT = 0, INSANE = 10, BLAZING = 50, FAST = 200, MEDIUM = 500, SLOW = 1000 };

pb_istream_t pb_in;
pb_ostream_t pb_out;

void setup() {
  Serial.begin(19200);

  pb_out = as_pb_ostream(Serial);
  pb_in = as_pb_istream(Serial);

  pinMode(Action::getRelayPin(Relay::Relay_ONE), OUTPUT);
  pinMode(Action::getRelayPin(Relay::Relay_TWO), OUTPUT);
  pinMode(Action::getRelayPin(Relay::Relay_THREE), OUTPUT);
  pinMode(Action::getRelayPin(Relay::Relay_FOUR), OUTPUT);

  ::StatusAction act(&pb_out);
  act.run();
}

void loop() {
  CommandRequest command = CommandRequest_init_default;
  pb_decode(&pb_in, CommandRequest_fields, &command);

  if (runCommand(&command)) {
    ::StatusAction act(&pb_out);
    act.run();
  }
}

bool runCommand(CommandRequest* command) {
  ActionRunner runner;
  if (command->command == NULL) { return false; }

  switch (command->command) {

    case CommandRequest_Command::CommandRequest_Command_ON: {
      runner.setActions(new OnAction(command->relay));
    } break;

    case CommandRequest_Command::CommandRequest_Command_OFF: {
      runner.setActions(new OffAction(command->relay));
    } break;

    case CommandRequest_Command::CommandRequest_Command_INVERT: {
      runner.setActions(new InvertAction(command->relay));
    } break;

    case CommandRequest_Command::CommandRequest_Command_SEQUENCE: {
      setupSequenceRunner(&runner, command->iterations, command->onMillis, command->offMillis, command->pauseMillis);
    } break;

    case CommandRequest_Command::CommandRequest_Command_FLASH: {
      setupFlashRunner(&runner, command->relay, command->iterations, command->onMillis, command->offMillis, command->pauseMillis);
    } break;

    case CommandRequest_Command::CommandRequest_Command_DEMO: {
      setupDemoRunner(&runner);
    } break;
  }

  runner.run();

  return true;
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
