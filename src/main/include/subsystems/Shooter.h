/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "frc/DriverStation.h"

#include "Recording.h"

class Shooter : public frc2::SubsystemBase {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  WPI_TalonSRX * Front;
  WPI_TalonSRX * Back;

  bool initialized = false;

  std::shared_ptr<nt::NetworkTable> table;
  
  Recording* m_recording;

 public:
  Shooter();
  void ShooterInit();
  void Periodic();
  void SetRecording(Recording* recording);
  void WriteData(double data);
  void SetMotorsPO(double front, double back);
  void SetMotorsVel(double front, double back);
  double GetMotorSpeed(bool back);
  void ChoosePipeline();
  double GetLimelightX();
  double GetLimelightY();
  void SetLimelightCamMode(int mode);
};
