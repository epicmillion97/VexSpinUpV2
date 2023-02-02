#include "vex.h"
#include "newAutonomous.h"

using namespace vex;




double kP = 0.013;
double kI = 0.000;
double kD = 0.003;

double turnkP = 0.0000001;
double turnkI = 0.0;
double turnkD = 0.0;


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
  FrontLeft.setBrake(brake);
  FrontRight.setBrake(brake);
  BackLeft.setBrake(brake);
  BackRight.setBrake(brake);
  while(enablePIDdrive){
    if(resetDriveSensors){
      resetDriveSensors = false;
      FrontLeft.setPosition(0, degrees);
      FrontRight.setPosition(0, degrees);
    }


    // lateral movement PID
    int frontLeftMotorPosition = FrontLeft.position(degrees);
    int frontRightMotorPosition = FrontRight.position(degrees);
    int backLeftMotorPosition = FrontLeft.position(degrees);
    int backRightMotorPosition = FrontRight.position(degrees);


    int averagePosition = ((frontLeftMotorPosition+frontRightMotorPosition+backLeftMotorPosition+backRightMotorPosition)/4);

    error = desiredValue - averagePosition;
    deriative = error - prevError;
    totalError += error;

    double lateralMotorPower = (error * kP + deriative * kD + totalError * kI);

    // turning movement PID
    //int turnDifference = Inertial.rotation(deg);

    turnError = desiredTurnValue - Inertial.rotation(deg);
    turnDeriative = turnError - turnPrevError;
    turnTotalError += turnError;
    double turnMotorPower = turnError * turnkP + turnDeriative + turnkD + turnTotalError + turnkI;


    Controller1.Screen.clearLine(2);
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print(averagePosition);

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


void newAutonomous(){
  task bill(drivePID);
  resetDriveSensors = true;
  
  desiredValue = 48/((4*3.141)/360); // 687.67 = tile
  desiredTurnValue = 0;
  wait(2000, msec);
  resetDriveSensors = true;
  desiredValue = -24/((4*3.141)/360);
  wait(2000, msec);

  resetDriveSensors = true;
  //desiredTurnValue = 90;
  desiredValue = 24/((4*3.141)/360); // 687.67 = tile
  desiredTurnValue = 0;
  wait(2000, msec);
  resetDriveSensors = true;
  desiredValue = -48/((4*3.141)/360);
  wait(2000, msec);
}