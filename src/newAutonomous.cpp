#include "vex.h"
#include "newAutonomous.h"

using namespace vex;


double kP = 0.009;
double kI = 0.001;
double kD = 0.006;

double turnkP = 0.11;
double turnkI = 0.00;
double turnkD = 0.01;


int desiredValue = 0;
int desiredTurnValue =0;

int error; //sensorvalue - desiredvalue: position
int prevError = 0; // 20 millseconds ago
int deriative; // error - prevError: speed
int totalError; // error + totalError

int turnError; //sensorvalue - desiredvalue: position
int turnPrevError = 0; // 20 millseconds ago
int turnDeriative; // error - prevError: speed
int turnTotalError; // error + totalError

bool resetDriveSensors = false;

bool enablePIDdrive = true;


int drivePID(){
  float startTime;
  //FrontLeft.setBrake(brake);
  //FrontRight.setBrake(brake);
  //BackLeft.setBrake(brake);
  //BackRight.setBrake(brake);
  while(enablePIDdrive){
    if(resetDriveSensors){
      resetDriveSensors = false;
      FrontLeft.setPosition(0, degrees);
      FrontRight.setPosition(0, degrees);
      BackLeft.setPosition(0, degrees);
      BackRight.setPosition(0, degrees);
      Inertial.resetRotation();
      startTime = Brain.Timer.time(sec);
    }

    /////////////////////////////
    // lateral movement PID
    /////////////////////////////
    int frontLeftMotorPosition = FrontLeft.position(degrees);
    int frontRightMotorPosition = FrontRight.position(degrees);
    int backLeftMotorPosition = FrontLeft.position(degrees);
    int backRightMotorPosition = FrontRight.position(degrees);

    int averagePosition = ((frontLeftMotorPosition+frontRightMotorPosition+backLeftMotorPosition+backRightMotorPosition)/4);

    error = desiredValue - averagePosition;
    deriative = error - prevError;
    totalError += error;

    double lateralMotorPower = (error * kP + deriative * kD + totalError * kI);

    ////////////////////////////
    // turning movement PID
    /////////////////////////////
    turnError = desiredTurnValue - Inertial.rotation(deg);
    turnDeriative = turnError - turnPrevError;
    turnTotalError += turnError;
    double turnMotorPower = turnError * turnkP + turnDeriative * turnkD + turnTotalError * turnkI;
    
    Controller1.Screen.clearLine(2);
    Controller1.Screen.setCursor(2,1);
    float diffTime = Brain.Timer.time(sec) - startTime;
    Controller1.Screen.print(diffTime);

    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3,1);
    Controller1.Screen.print(Inertial.rotation(deg));

    FrontLeft.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    FrontRight.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);
    BackLeft.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    BackRight.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);

    prevError = error;
    task::sleep(20);
  };
  return 1;
}

float frominches(float inches){
  return inches/((4*3.141)/360);  // 687.67 = tile
}

void startIntake2(){
  ColorRoller.setVelocity(40,percent); // Set Velocity of Intake
  Conveyor1.setVelocity(45,percent); // Set Velocity of Conveyor1
  ColorRoller.spin(forward); // Start Motor
  Conveyor1.spin(forward); // Start Motor
}

void stopIntake2(){
  ColorRoller.setVelocity(0, percent);
  Conveyor1.setVelocity(0, percent);
}

void startColor2(){
  ColorRoller.setVelocity(-45,percent); // Set Velocity of Intake
  ColorRoller.spin(forward); // Start Motor
}

void stopColor2(){
  ColorRoller.setVelocity(0, percent);
}

void startFlywheel2(int powera){
  Flywheel.setVelocity(powera, percent);
  Flywheel.spin(forward);
}

void stopFlywheel2(){
  Flywheel.setVelocity(0, percent);
}

void startConveyorToFlywheel2(){
  Conveyor2.setVelocity(55, percent);
  Conveyor2.spin(forward);
}

void startConveyorToFlywheelIntermittent2(){
  Conveyor2.setVelocity(75, percent);
  Conveyor2.spin(forward);
  wait(.5, sec);
  Conveyor2.setVelocity(20, percent);
  wait(.5, sec);
  Conveyor2.setVelocity(75, percent);
}

void stopConveyorToFlywheel2(){
  Conveyor2.setVelocity(0, percent);
}



void donothing(){
  enablePIDdrive = false;
}

void newAutonomous(){
  enablePIDdrive = true;
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("NEW A-3");
  task bill(drivePID);

  resetDriveSensors = true;
  desiredValue = frominches(10);
  desiredTurnValue = 0;
  wait(1000, msec);

  resetDriveSensors = true;
  desiredValue = frominches(0);
  desiredTurnValue = 90;
  wait(1000, msec);

  resetDriveSensors = true;
  desiredValue = frominches(20);
  desiredTurnValue = 0;
  wait(1500, msec);

  resetDriveSensors = true;
  desiredValue = frominches(0);
  desiredTurnValue = 90;
  wait(1000, msec);

//

  startColor2();
  wait(.5, sec);
  resetDriveSensors = true;
  desiredValue = frominches(8);
  desiredTurnValue = 0;
  wait(1000, msec);

  resetDriveSensors = true;
  desiredValue = frominches(-6);
  desiredTurnValue = 0;
  wait(1000, msec);
  stopColor2();

//

  startFlywheel2(85);
  resetDriveSensors = true;
  desiredValue = frominches(0);
  desiredTurnValue = 145;
  wait(1500, msec);

  resetDriveSensors = true;
  desiredValue = frominches(24*2.5);
  desiredTurnValue = 0;
  wait(2000, msec);


//

  resetDriveSensors = true;
  desiredValue = frominches(0);
  desiredTurnValue = 180;
  wait(1500, msec);


  startConveyorToFlywheel2();
  wait(1.5, sec);
  stopConveyorToFlywheel2();
  wait(.7, sec);
  startConveyorToFlywheel2();
  wait(1.5, sec);
  stopConveyorToFlywheel2();
  wait(.7, sec);
  startConveyorToFlywheel2();
  wait(1.5, sec);
  stopConveyorToFlywheel2();
  // stop flywheel
  stopFlywheel2();
  enablePIDdrive = true;
}