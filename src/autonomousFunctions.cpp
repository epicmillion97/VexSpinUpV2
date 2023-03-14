#include "vex.h"
#include "autonomousFunctions.h"

using namespace vex;

// AUTONOMOUS VARIABLES

float wheelDiameter = 3.5;
float wheelCircumference = wheelDiameter * 3.141; //inches
float turningDiameter = 22;

float tile = 24;
float translationSpeed = 75;
float turningSpeed = 50;


void driveForward(float inches, float speed) {
    float inchesPerDegree = wheelCircumference / 360;
    float degrees = inches / inchesPerDegree;

    FrontRight.startRotateFor(degrees, deg, speed, vex::velocityUnits::pct);
    FrontLeft.startRotateFor(degrees, deg, speed, vex::velocityUnits::pct);
    BackRight.startRotateFor(degrees, deg, speed, vex::velocityUnits::pct);
    BackLeft.rotateFor(degrees, deg, speed, vex::velocityUnits::pct);
}

void drivegay() {
    FrontRight.setVelocity(50, percent);
    FrontRight.spin(forward);
    FrontLeft.setVelocity(50, percent);
    FrontLeft.spin(forward);
    BackRight.setVelocity(50, percent);
    BackRight.spin(forward);
    BackLeft.setVelocity(50, percent);
    BackLeft.spin(forward);
}

void drivegaystop(){
    FrontRight.setVelocity(0, percent);
    FrontRight.spin(forward);
    FrontLeft.setVelocity(0, percent);
    FrontLeft.spin(forward);
    BackRight.setVelocity(0, percent);
    BackRight.spin(forward);
    BackLeft.setVelocity(0, percent);
    BackLeft.spin(forward);

}

void driveBackward(float inches, float speed) {
    float inchesPerDegree = wheelCircumference / 360;
    float degrees = inches / inchesPerDegree;

    FrontRight.startRotateFor(-degrees, deg, speed, vex::velocityUnits::pct);
    FrontLeft.startRotateFor(-degrees, deg, speed, vex::velocityUnits::pct);
    BackRight.startRotateFor(-degrees, deg, speed, vex::velocityUnits::pct);
    BackLeft.rotateFor(-degrees, deg, speed, vex::velocityUnits::pct);
}

void driveTurn(float degrees, float turningSpeed){
  float turningRatio = turningDiameter / wheelDiameter;
  float wheelDegrees = turningRatio * degrees;
    FrontRight.startRotateFor(-wheelDegrees, deg, turningSpeed, vex::velocityUnits::pct);
    FrontLeft.startRotateFor(wheelDegrees, deg, turningSpeed, vex::velocityUnits::pct);
    BackRight.startRotateFor(-wheelDegrees, deg, turningSpeed, vex::velocityUnits::pct);
    BackLeft.rotateFor(wheelDegrees, deg, turningSpeed, vex::velocityUnits::pct);
    
}

void driveTurn2(float degrees, float turningSpeed){
  Inertial.setRotation(0, deg);
  float turningRatio = turningDiameter / wheelDiameter;
  float wheelDegrees = turningRatio * degrees;
  FrontRight.startRotateFor(-wheelDegrees, deg, turningSpeed, vex::velocityUnits::pct);
  FrontLeft.startRotateFor(wheelDegrees, deg, turningSpeed, vex::velocityUnits::pct);
  BackRight.startRotateFor(-wheelDegrees, deg, turningSpeed, vex::velocityUnits::pct);
  BackLeft.startRotateFor(wheelDegrees, deg, turningSpeed, vex::velocityUnits::pct);
  while(Inertial.rotation(deg) < degrees){
    wait(10, msec);
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print(Inertial.rotation(deg));
  }
    FrontRight.stop();
    FrontLeft.stop();
    BackRight.stop();
    BackLeft.stop();
}

void driveStrafe(float inches){
    float speed = 50;
    float inchesPerDegree = wheelCircumference / 360;
    float degrees = (inches / inchesPerDegree);
    FrontRight.startRotateFor(-degrees, deg, speed, vex::velocityUnits::pct);
    FrontLeft.startRotateFor(degrees, deg, speed, vex::velocityUnits::pct);
    BackRight.startRotateFor(degrees, deg, speed, vex::velocityUnits::pct);
    BackLeft.rotateFor(-degrees, deg, speed, vex::velocityUnits::pct);
}

void startIntake(){
  ColorRoller.setVelocity(40,percent); // Set Velocity of Intake
  Conveyor1.setVelocity(45,percent); // Set Velocity of Conveyor1
  ColorRoller.spin(forward); // Start Motor
  Conveyor1.spin(forward); // Start Motor
}

void stopIntake(){
  ColorRoller.setVelocity(0, percent);
  Conveyor1.setVelocity(0, percent);
}

void startColor(){
  ColorRoller.setVelocity(-45,percent); // Set Velocity of Intake
  ColorRoller.spin(forward); // Start Motor
}

void stopColor(){
  ColorRoller.setVelocity(0, percent);
}

void startFlywheel(int powera){
  Flywheel.setVelocity(powera, percent);
  Flywheel.spin(forward);
}

void stopFlywheel(){
  Flywheel.setVelocity(0, percent);
}

void startConveyorToFlywheel(){
  Conveyor2.setVelocity(55, percent);
  Conveyor2.spin(forward);
}

void startConveyorToFlywheelIntermittent(){
  Conveyor2.setVelocity(75, percent);
  Conveyor2.spin(forward);
  wait(.5, sec);
  Conveyor2.setVelocity(20, percent);
  wait(.5, sec);
  Conveyor2.setVelocity(75, percent);
}

void stopConveyorToFlywheel(){
  Conveyor2.setVelocity(0, percent);
}

void stopEveryting(){
  
}

void autonomousinit(){
  
}


void autonomousTest(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("A-Act - T");

  driveForward(tile*2, translationSpeed);
  wait(1,sec);
  driveTurn(90, turningSpeed);
  wait(3, sec);
  driveStrafe(tile);
  
}


void autonomousOne(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("A-Act - 1");
  // random shit - intake. then drive 2 tiles + turn and shoot + come back 2 tiles.
  startIntake();
  wait(6, sec);
  

  driveForward(2*tile, translationSpeed);

  wait(.5,sec); //delay
  driveTurn(-90, turningSpeed);
  wait(1, sec);
  startFlywheel(80);
  wait(3,sec);
  stopIntake();

  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  wait(.5, sec);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();

  stopFlywheel();
  wait(.5,sec); //delay
  driveTurn(-90, turningSpeed);
  driveForward(2*tile, translationSpeed);

  driveTurn(180, turningSpeed);

}

void autonomousTwo(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("A-Act - 2");
  // if placed on the roller and facing it bottom corner

  // get roller
  startIntake();
  drivegay();
  wait(.5,sec);
  drivegaystop();

  
  driveBackward(.5*tile, translationSpeed);
  // face diagonal facing the three disc pile
  driveTurn(-136, turningSpeed);
  driveStrafe(-2); // NOT SURE IF WORKS BUT WOULD MOVE LEFT OF DISC PILE

  // move towards center
  startFlywheel(80);
  driveForward(2*tile, translationSpeed);
  stopIntake();
  //spin around
  driveTurn(-180, turningSpeed);
  // shooting discs
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  wait(.5, sec);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  // stop flywheel
  stopFlywheel();
  
}

void autonomousThree(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("A-Act - 3");
  // if placed on the two tiles near the roller facing out to the field
  
  // get to roller
  driveForward(4.5, translationSpeed); // forward 3 inches to get off wall
  driveTurn(90, turningSpeed);
  driveForward(21, translationSpeed);
  driveTurn(90, turningSpeed);
  // run into roller
  
  startColor();
  wait(.5, sec);
  drivegay();
  wait(.75,sec);
  drivegaystop();
  // get away from roller
  
  stopColor();
  driveBackward(4, translationSpeed);
  

  startFlywheel(81);
  driveTurn(145, turningSpeed);
  // move into the center for a shot
  //startIntake();
  driveStrafe(-2);
  driveForward(2.5*tile, translationSpeed);
  //stopIntake();

  // shooting discs
  driveTurn(174, turningSpeed);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  wait(1.5, sec);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  wait(1.5, sec);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  // stop flywheel
  stopFlywheel();
  

}

void autonomousPhil(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("A-Act - 3");
  // if placed on the two tiles near the roller facing out to the field
  
  // get to roller
  driveForward(4.5, translationSpeed); // forward 3 inches to get off wall
  driveTurn(90, turningSpeed);
  driveForward(20, translationSpeed);
  driveTurn(90, turningSpeed);
  // run into roller
  
  startColor();
  wait(.5, sec);
  drivegay();
  wait(.75,sec);
  drivegaystop();
  // get away from roller
  
  stopColor();
  driveBackward(3, translationSpeed);
}

void autonomousYaseen(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("A-Act - Y");
  // if placed on the two tiles near the roller facing out to the field
  
  // get to roller
  driveForward(4.5, translationSpeed); // forward 3 inches to get off wall
  driveTurn(90, turningSpeed);
  driveForward(21, translationSpeed);
  driveTurn(90, turningSpeed);
  // run into roller
  
  startColor();
  wait(.5, sec);
  drivegay();
  wait(.75,sec);
  drivegaystop();
  // get away from roller
  
  stopColor();
  driveBackward(5, translationSpeed);
  

  startFlywheel(80);
  driveTurn(100, turningSpeed);
  // move into the center for a shot
  //startIntake();
  driveStrafe(5);
  driveForward(1.5 * tile, translationSpeed);
  //stopIntake();
  
  // shooting discs
  driveTurn(85, turningSpeed);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  wait(1.5, sec);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  wait(1.5, sec);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  // stop flywheel
  stopFlywheel();
  

}

void autonomousNoah(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("A-Act - N");
  // if placed on the two tiles near the roller facing out to the field  
  startColor();
  wait(.5, sec);
  drivegay();
  wait(.75,sec);
  drivegaystop();
  // get away from roller
  
  stopColor();
  driveBackward(4, translationSpeed);
}


void autonomousSkills(){
Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("A-Act - 3");
  // if placed on the two tiles near the roller facing out to the field
  
  // get to roller
  driveForward(4.5, translationSpeed); // forward 3 inches to get off wall
  driveTurn(90, turningSpeed);
  driveForward(20, translationSpeed);
  driveTurn(90, turningSpeed);
  // run into roller
  
  startColor();
  wait(.5, sec);
  drivegay();
  wait(1.25,sec);
  drivegaystop();
  // get away from roller
  
  stopColor();
  driveBackward(4, translationSpeed);
  

  startFlywheel(84);
  driveTurn(145, turningSpeed);
  // move into the center for a shot
  //startIntake();
  driveForward(2.5*tile, translationSpeed);
  //stopIntake();

  // shooting discs
  driveTurn(174, turningSpeed);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  wait(1.5, sec);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  wait(1.5, sec);
  startConveyorToFlywheel();
  wait(1.5, sec);
  stopConveyorToFlywheel();
  // stop flywheel
  stopFlywheel();

  //
  driveForward(1.5*tile, translationSpeed);
  driveTurn(-45, turningSpeed);

  startColor();
  wait(.5, sec);
  drivegay();
  wait(3,sec);
  drivegaystop();
  // get away from roller
  
  stopColor();
  driveBackward(8, translationSpeed);

  driveTurn(-45, turningSpeed);
  driveBackward(tile, translationSpeed);
  Pneumatics.set(true);
  driveBackward(2.5*tile, translationSpeed);



}

void autonomousNOTHING(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("A-Act - Non");
}