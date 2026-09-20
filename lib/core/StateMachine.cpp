#include "StateMachine.h"

#include "robot/Robot.h"

void StateMachine::init(Robot &r) {

}

void StateMachine::tick(Robot &r) {
  r.update();

  // Update StateMachine state here

  a->run(r);
}
