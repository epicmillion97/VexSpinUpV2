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




bool enablePIDdrive = false;

int drivePID(){
  while(enablePIDdrive){

  };
  return 1;
}


void newAutonomous(){

}