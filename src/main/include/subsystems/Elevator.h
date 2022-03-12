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

class Elevator : public frc2::SubsystemBase {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  bool initialized = false;

  WPI_TalonSRX * Motor;
  frc::DigitalInput ProximitySensor1{0};
  frc::DigitalInput ProximitySensor2{1};
  
  Recording* m_recording;

 public:
  Elevator();
  void ElevatorInit();
  void Periodic();
  void SetRecording(Recording* recording);
  void SetMotorPO(double PO);
  bool GetSwitch1();
  bool GetSwitch2();
};
