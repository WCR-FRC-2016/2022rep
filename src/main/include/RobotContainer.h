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
#include "subsystems/Climber.h"
#include "commands/ArcadeDrive.h"
#include "commands/LIDARTest.h"
#include "commands/Center.h"
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
  
  // Driver Left Bumper: Adjust speed -0.1
  frc2::Button m_driverLB{[&] {return m_driverStick.GetLeftBumper();}};
  frc2::InstantCommand m_AdjustSpeedDown{[this] {m_driveBase.adjustSpeed(-0.1);} , {&m_driveBase} };
  
  // Driver Right Bumper: Adjust speed +0.1
  frc2::Button m_driverRB{[&] {return m_driverStick.GetRightBumper();}};
  frc2::InstantCommand m_AdjustSpeedUp{[this] {m_driveBase.adjustSpeed(0.1);} , {&m_driveBase} };
  
  // Driver B: Reverse Drive
  frc2::Button m_driverB{[&] {return m_driverStick.GetBButton();}};
  frc2::InstantCommand m_ReverseDrive{[this] {m_driveBase.reverseDrive();} , {&m_driveBase} };

  // Manip Either Trigger: Shoot
  frc2::Button m_manET{[&] {return (0.2 < m_manStick.GetRightTriggerAxis()) || (0.2 < m_manStick.GetLeftTriggerAxis());} };
  frc2::InstantCommand m_ManualShoot{[this] {m_shooter.SetMotorsPO(-pow(m_manStick.GetRightTriggerAxis(), 2), -pow(m_manStick.GetLeftTriggerAxis(), 2));}, {&m_shooter} };
  
  // Manip A: Center
  frc2::Button m_manA{[&] {return m_manStick.GetAButton();}};
 
  // Manip Y: Swap Vision Target
  frc2::Button m_manY{[&] {return m_manStick.GetYButton();}};
  frc2::InstantCommand m_PipelineSwap{[this] {m_shooter.ChoosePipeline();} , {&m_shooter} };

  frc2::RunCommand m_NoShoot{[this] {m_shooter.SetMotorsPO(0, 0);}, {&m_shooter} };
  frc2::RunCommand m_ClimbControls{[this] {
    double m_turn   = m_manStick.GetRightX();
    double m_extend = m_manStick.GetLeftY();
    double passTurn   = (abs(m_turn*1000)   > 200?m_turn:0.0);
    double passExtend = (abs(m_extend*1000) > 200?m_extend:0.0);
    m_climber.SetMotorsPO(passTurn, passExtend);
  }, {&m_climber}};
  
  int command_no;
 
 private:
  frc::XboxController m_driverStick{0};
  frc::XboxController m_manStick{1};
  
  DriveBase m_driveBase;
  Shooter m_shooter;
  Climber m_climber;

  void ConfigureButtonBindings();

  std::vector<std::string> commands;
  std::fstream file {"/home/lvuser/wcrj/autonomous.txt"};
  std::fstream configfile {"/home/lvuser/wcrj/config.txt"};
};