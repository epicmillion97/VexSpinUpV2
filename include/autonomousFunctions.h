#ifndef AUTONOMOUSFUNCTIONS_H
#define AUTONOMOUSFUNCTIONS_H

void driveForward(float inches, float speed);
void driveTurn(float degrees, float turningSpeed);
void driveStrafe(float inches);
void startIntake();
void stopIntake();
void startFlywheel(int powera);
void stopFlywheel();
void startConveyorToFlywheel();
void startConveyorToFlywheelIntermittent();
void stopConveyorToFlywheel();

void autonomousTest();
void autonomousOne();
void autonomousTwo();
void autonomousThree();
void autonomousSkills();
void autonomousNOTHING();
void autonomousPhil();
void autonomousYaseen();
void autonomousNoah();
#endif