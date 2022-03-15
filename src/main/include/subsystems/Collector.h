/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>

class Collector : public frc2::SubsystemBase {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  bool initialized = false;

  double LiftMotorPO = 0.0;

  WPI_TalonSRX * Motor;
  WPI_TalonSRX * LiftMotor;
  frc::DigitalInput HallEffectSensor1{2};
  frc::DigitalInput HallEffectSensor2{3};

  void SetLiftMotorPO(double PO);

 public:
  Collector();
  void CollectorInit();
  void Periodic();
  void SetMotorPO(double PO);
  void SetLiftMotorPOHold(double PO);
  void SwapLiftMotorPOHold();
};
