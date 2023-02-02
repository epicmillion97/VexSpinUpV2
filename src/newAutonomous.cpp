#include "vex.h"
#include "newAutonomous.h"

using namespace vex;

// AUTONOMOUS VARIABLES
float wheelDiameter = 3.5;
float wheelCircumference = wheelDiameter * 3.141; //inches
float turningDiameter = 22;

float tile = 24;
float translationSpeed = 75;
float turningSpeed = 50;



double kP = 0.0;
double kI = 0.0;
double kD = 0.0;

double turnkP = 0.0;
double turnkI = 0.0;
double turnkD = 0.0;


int desiredValue = 200;
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
  while(enablePIDdrive){
    if(resetDriveSensors){
      resetDriveSensors = false;
      FrontLeft.setPosition(0, degrees);
      FrontRight.setPosition(0, degrees);
    }


    // lateral movement PID
    int leftMotorPosition = FrontLeft.position(degrees);
    int rightMotorPosition = FrontRight.position(degrees);

    int averagePosition = (leftMotorPosition+rightMotorPosition)/2;

    error = averagePosition - desiredValue;
    deriative = error - prevError;
    totalError += error;

    double lateralMotorPower = (error * kP + deriative * kD + totalError * kI);

    // turning movement PID
    int turnDifference = leftMotorPosition - rightMotorPosition;

    turnError = turnDifference - desiredTurnValue;
    turnDeriative = turnError - turnPrevError;
    turnTotalError += turnError;
    double turnMotorPower = turnError * turnkP + turnDeriative + turnkD + turnTotalError + turnkI;



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

  desiredValue = 300;
  desiredTurnValue = 600;

}