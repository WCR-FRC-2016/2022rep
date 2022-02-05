/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc2/command/SubsystemBase.h>
//#include "networktables/NetworkTable.h"
//#include "networktables/NetworkTableInstance.h"

class Shooter : public frc2::SubsystemBase {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  bool initialized = false;

  //std::shared_ptr<nt::NetworkTable> table;

 public:
  Shooter();
  void ShooterInit();
  void Periodic();
};
