#ifndef VARIABLES_H
#define VARIABLES_H

#pragma once

// VARIABLES
float MaxRotationSpeed = .55; // Normal Steering Speed no Turbo
float MaxTranslationSpeed = .80; // Normal Driving Speed no Turbo
float TurboRotationSpeed = .85; // Turbo Rotation Speed 
float TurboTranslationSpeed = 1; // Turbo Translation Speed
float currentMaxRotationSpeed = MaxRotationSpeed;
float currentMaxTranslationSpeed = MaxTranslationSpeed;

int conveyor1Speed = 45; //Normal Vertical Conveyor Speed 
int conveyor1SpeedTurbo = 85; //Turbo Vertical Conveyor Speed 
int colorRollerSpeed = 30; // Normal Intake/ColorRoller Speed
int colorRollerSpeedTurbo = 80; // Turbo Intake/ColorRoller Speed
int currentConveyor1Speed = conveyor1Speed;
int currentcolorRollerSpeed = colorRollerSpeed;
 
int conveyor2Speed = 55;
int conveyor2SpeedTurbo = 90;
int currentConveyor2Speed = conveyor2Speed;

int flywheelStrength = 90; // Flywheel Strength 

bool turboModeActive = false; // Current Turbo Status
bool visionDrivingActive = false; // BETA IMAGE DETECTION Status
bool autonoumousActive = false; // autonmous active status

// AUTONOMOUS VARIABLES


#endif