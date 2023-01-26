using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FrontLeft;
extern motor BackLeft;
extern motor FrontRight;
extern motor BackRight;
extern motor Flywheel;
extern motor ColorRoller;
extern motor Conveyor1;
extern motor Conveyor2;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );