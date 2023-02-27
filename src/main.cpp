/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Hayden                                           */
/*    Created:      Thu Jan 26 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         1               
// FrontRight           motor         2               
// BackLeft             motor         3               
// BackRight            motor         4               
// Flywheel             motor         5               
// ColorRoller          motor         6               
// Conveyor1            motor         7               
// Conveyor2            motor         8               
// Controller1          controller                    
// Inertial             inertial      10              
// Pneumatics           digital_out   A               
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "variables.h"
#include "autonomousFunctions.h"
//#include "newAutonomous.h"


using namespace vex;

competition Competition;


float cap(float inputVal, float maxMinVal) { // Cap allow full use of motor range with steering
  if (inputVal > maxMinVal){
    return maxMinVal;
  } else if (inputVal < -maxMinVal) {
    return -maxMinVal;
  } else{
    return inputVal;
  };
  // if inputVal is greater than max min val, return max min val
  // if less than min val then return -maxMinVal
  // else return inputVal
}


void turbocode(){ // BETA TURBO CODE CALLBACK FUNCTION
  if(turboModeActive == false){
    currentMaxRotationSpeed = TurboRotationSpeed; // Sets current rotation speed to turbo value
    currentMaxTranslationSpeed = TurboTranslationSpeed; // Sets current translation speed to turbo value
    currentConveyor1Speed = conveyor1SpeedTurbo;
    currentcolorRollerSpeed = colorRollerSpeedTurbo;
    currentConveyor2Speed = conveyor2SpeedTurbo;
    turboModeActive = true;

    Controller1.Screen.clearLine(3);  
    Controller1.Screen.setCursor(3, 1); 
    Controller1.Screen.print("TURBO MODE ACTIVE");
    wait(100, msec);
  } else if(turboModeActive == true){
    currentMaxRotationSpeed = MaxRotationSpeed; // Sets current max rotation speed back to default
    currentMaxTranslationSpeed = MaxTranslationSpeed; // Sets current translation speed back to default
    currentConveyor1Speed = conveyor1Speed;
    currentcolorRollerSpeed = colorRollerSpeed; 
    currentConveyor2Speed = conveyor2Speed;
    turboModeActive = false;

    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(" ");
    wait(100, msec);
  }
}


void driverControl(){
  FrontLeft.stop(brake);
  BackLeft.stop(brake);
  FrontRight.stop(brake);
  BackRight.stop(brake);
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("DriveR");
  while (69==69){
  //THE MOVE PLACE
  float V = Controller1.Axis3.position(percent); // Forward and backwards
  float H = Controller1.Axis4.position(percent); // Strafe
  float S = Controller1.Axis1.position(percent); // Steering
    
  float vA = V * currentMaxTranslationSpeed; // Limit Forward/Backwards Speed
  float hA = H * currentMaxTranslationSpeed; // Limit Strafe Speed
  float sA = S * currentMaxRotationSpeed; // Limit Steering Speed

  float drivetrainMax = 100 - fabsf(sA); // Max motor movement given steering is constant

  // Set Motor Velocity with Steering Prioritized with 
  float FL_motor_command = sA + cap(vA + hA, drivetrainMax);
  float BL_motor_command = sA + cap(vA + -hA, drivetrainMax);
  float FR_motor_command = -sA + cap(vA + -hA, drivetrainMax);
  float BR_motor_command = -sA + cap(vA + hA, drivetrainMax);
  // Assign Proper Velocity for Each Motor
  FrontLeft.setVelocity(FL_motor_command, percent);
  BackLeft.setVelocity(BL_motor_command, percent);
  FrontRight.setVelocity(FR_motor_command, percent);
  BackRight.setVelocity(BR_motor_command, percent);
  // Start Motors
  FrontLeft.spin(forward);
  FrontRight.spin(forward);
  BackLeft.spin(forward);
  BackRight.spin(forward);

  //int frontLeftMotorPosition = FrontLeft.position(degrees);
  //int frontRightMotorPosition = FrontRight.position(degrees);
  //int backLeftMotorPosition = FrontLeft.position(degrees);
  //int backRightMotorPosition = FrontRight.position(degrees);
  //Controller1.Screen.setCursor(2, 1);
  //Controller1.Screen.print((frontLeftMotorPosition+frontRightMotorPosition+backLeftMotorPosition+backRightMotorPosition)/4);
  //Controller1.Screen.setCursor(3, 1);
  //Controller1.Screen.print(Inertial.rotation(deg));

  if(Controller1.ButtonA.pressing() == true){
    Pneumatics.set(true);
  } else{
    Pneumatics.set(false);
  }
  if(Controller1.ButtonY.pressing() == true) { //This is for Conveyor1 and Intake
    ColorRoller.setVelocity(currentcolorRollerSpeed,percent); // Set Velocity of Intake
    Conveyor1.setVelocity(currentConveyor1Speed,percent); // Set Velocity of Conveyor1
    ColorRoller.spin(forward); // Start Motor
    Conveyor1.spin(forward); // Start Motor
  } else if(Controller1.ButtonX.pressing() == true) { // This is for Conveyor1 and Intake Rejection
    ColorRoller.setVelocity(-currentcolorRollerSpeed,percent); // Set Velocity of Intake
    Conveyor1.setVelocity(-currentConveyor1Speed,percent); // Set Velocity of Conveyor1
    ColorRoller.spin(forward); // Start Motor 
    Conveyor1.spin(forward); // Start Motor
  } else if (Controller1.ButtonB.pressing() == true) {
      ColorRoller.setVelocity(20,percent);
    } else {
    ColorRoller.setVelocity(0,percent); // otherwise stop motors
    Conveyor1.setVelocity(0,percent);
  }

  if(Controller1.ButtonR2.pressing() == true) { //This is for the Flywheel
    Flywheel.setVelocity(flywheelStrength, percent); // Set Velocity of Flywheel to 100%
    Flywheel.spin(forward); // Start Motor
  } else {
    Flywheel.setVelocity(0,percent); // Stop Motor Velocity
  }

  if(Controller1.ButtonL2.pressing() == true) { //This is for Conveyor2 Forwards
    Conveyor2.setVelocity(currentConveyor2Speed,percent); // Set Velocity
    Conveyor2.spin(forward); // Start Motor
  } else if(Controller1.ButtonL1.pressing() == true) { //This is for Conveyor2 Reverse
    Conveyor2.setVelocity(-currentConveyor2Speed,percent); // Set Velocity
    Conveyor2.spin(forward); // Start Motor
  } else {
    Conveyor2.setVelocity(0,percent); // Stop Motor Velocity 
  }

  if(Controller1.ButtonLeft.pressing() == true){ //Decreases flywheel strength
    if(flywheelStrength > 10){
      flywheelStrength-=5;
      Controller1.Screen.clearLine(2);
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print(flywheelStrength);
    }
    wait(250,msec);
  } else if(Controller1.ButtonRight.pressing() == true){ //Increases flywheel strength
    if(flywheelStrength < 100){
      flywheelStrength+=5;
      Controller1.Screen.clearLine(2);
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print(flywheelStrength);
    }
    wait(250,msec);
  }
  Controller1.ButtonR1.pressed(turbocode); // Activate Turbo Mode

  wait(20,msec);
  }
}


void setup(){ // Setup Code -- Only Runs Once
  // Screen Setup
  Inertial.calibrate();
  while( Inertial.isCalibrating()){
    wait(100, msec);
  }
  
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Hayden");

  Brain.Screen.drawImageFromFile("yaseencute.png", 1, 1);
  Brain.Screen.setCursor(1,1);
  Brain.Screen.setFillColor(vex::color(0,0,0));
  Brain.Screen.setCursor(12, 1);
  Brain.Screen.print("Programming by Hayden <3 <o/");

}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  setup();
  Competition.bStopTasksBetweenModes= true;
  Competition.bStopAllTasksBetweenModes = true; // maybe necessary?
  Competition.autonomous(autonomousPhil);
  Competition.drivercontrol(driverControl);
  

  while(420==420) {
    vexDelay(69);  //delay to limit resources
  }
}

// created by yaseen and hayden. the best

// number 5 - skills
// number 1 - none
// number 3 - two tile 