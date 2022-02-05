/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
//
// 2020Mar17 Walko - Added some comment and reordered some statements for better clarity
//
#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <math.h>

#include "subsystems/DriveBase.h"
#include "subsystems/Shooter.h"
#include "commands/ArcadeDrive.h"
#include "RobotMap.h"
#include "frc/XboxController.h"
#include <frc2/command/RunCommand.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/button/Button.h>

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();
  void ReadFile();
  void SetConfig();
  void OpenDriveBaseFile();
  void CloseDriveBaseFile();

  // Manip Either Trigger: Shoot
  frc2::Button m_manET{[&] {return (0.2 < m_manStick.GetRightTriggerAxis()) || (0.2 < m_manStick.GetLeftTriggerAxis());} };
  
  frc2::RunCommand m_NoShoot{[this] {m_shooter.SetMotorsPO(0, 0);}, {&m_shooter} };
  frc2::InstantCommand m_ManualShoot{[this] {m_shooter.SetMotorsPO(-pow(m_manStick.GetRightTriggerAxis(), 2), -pow(m_manStick.GetLeftTriggerAxis(), 2));}, {&m_shooter} };
  
  int command_no;
 
 private:
  frc::XboxController m_driverStick{0};
  frc::XboxController m_manStick{1};
  
  DriveBase m_driveBase;
  Shooter m_shooter;

  void ConfigureButtonBindings();

  std::vector<std::string> commands;
  std::fstream file {"/home/lvuser/wcrj/autonomous.txt"};
  std::fstream configfile {"/home/lvuser/wcrj/config.txt"};
};