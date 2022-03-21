/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>

#include <fstream>
#include <string>
//#include <AHRS.h>

class DriveBase : public frc2::SubsystemBase {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  bool initialized = false;
  double driveConstant = -1;
  double speed = 1;

  WPI_TalonSRX * FrontL;
  WPI_TalonSRX * FrontR;
  WPI_TalonSRX * BackL;
  WPI_TalonSRX * BackR;
  //AHRS * ahrs;
  frc::DifferentialDrive * _diffDrive;

  std::fstream recordfile {"/home/lvuser/wcrj/replay.txt", std::ios_base::out | std::ios_base::trunc};

 public:
  DriveBase();
  void DriveBaseInit();
  void Periodic();
  void ArcadeDrive(double xAxis, double yAxis);
  void RampSwitch(bool rampOn);
  void reverseDrive();
  double getSpeed();
  void setSpeed(double newSpeed);
  void openFile();
  void closeFile();
  void writeToFile(std::string msg);
};
