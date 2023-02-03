using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FrontLeft;
extern motor FrontRight;
extern motor BackLeft;
extern motor BackRight;
extern motor Flywheel;
extern motor ColorRoller;
extern motor Conveyor1;
extern motor Conveyor2;
extern controller Controller1;
extern inertial Inertial;
extern digital_out Pneumatics;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );