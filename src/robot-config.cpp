#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontLeft = motor(PORT1, ratio18_1, false);
motor FrontRight = motor(PORT2, ratio18_1, true);
motor BackLeft = motor(PORT3, ratio18_1, false);
motor BackRight = motor(PORT4, ratio18_1, true);
motor Flywheel = motor(PORT5, ratio18_1, true);
motor ColorRoller = motor(PORT6, ratio18_1, true);
motor Conveyor1 = motor(PORT7, ratio18_1, true);
motor Conveyor2 = motor(PORT8, ratio18_1, false);
controller Controller1 = controller(primary);
inertial Inertial = inertial(PORT10);
digital_out Pneumatics = digital_out(Brain.ThreeWirePort.A);
controller Controller2 = controller(partner);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}