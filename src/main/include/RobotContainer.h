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
#include "subsystems/Collector.h"
#include "subsystems/Elevator.h"
#include "commands/ArcadeDrive.h"
#include "commands/LIDARTest.h"
#include "commands/Center.h"
#include "commands/Collect.h"
#include "commands/Shoot.h"
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
  
  // Driver Left Trigger: Adjust speed -0.1
  frc2::Button m_driverLT{[&] {return 0.5 < m_driverStick.GetLeftTriggerAxis();}};
  frc2::InstantCommand m_AdjustSpeedDown{[this] {m_driveBase.setSpeed(m_driveBase.getSpeed()-0.1);} , {&m_driveBase} };
  
  // Driver Right Trigger: Adjust speed +0.1
  frc2::Button m_driverRT{[&] {return 0.5 < m_driverStick.GetRightTriggerAxis();}};
  frc2::InstantCommand m_AdjustSpeedUp{[this] {m_driveBase.setSpeed(m_driveBase.getSpeed()+0.1);} , {&m_driveBase} };
  
  // Driver Right Bumper: Swap speed to 1 or 0.5 (0.5 if at 1, otherwise 1)
  frc2::Button m_driverRB{[&] {return m_driverStick.GetRightBumper();}};
  frc2::InstantCommand m_SwapSpeed{[this] {m_driveBase.setSpeed(m_driveBase.getSpeed()>0.95?0.5:1.0);} , {&m_driveBase} };
  
  // Driver B: Reverse Drive
  frc2::Button m_driverB{[&] {return m_driverStick.GetBButton();}};
  frc2::InstantCommand m_ReverseDrive{[this] {m_driveBase.reverseDrive();} , {&m_driveBase} };

  /*
  // Manip Either Trigger: Shoot (old test command for calibration)
  frc2::Button m_manET{[&] {return (0.2 < m_manStick.GetRightTriggerAxis()) || (0.2 < m_manStick.GetLeftTriggerAxis());}};
  frc2::InstantCommand m_ManualShoot{[this] {m_shooter.SetMotorsPO(-pow(m_manStick.GetRightTriggerAxis(), 2), -pow(m_manStick.GetLeftTriggerAxis(), 2));}, {&m_shooter} };
  */
  
  // Manip DPad Up: Adjust shooting front +
  frc2::Button m_manDPadU{[&] {return m_manStick.GetPOV()==0;}};
  frc2::InstantCommand m_AdjustSpeedFrontUp{[this] {robotConfig["shootingSpeedFront"]+=robotConfig["shootingSpeedShift"];} , {} };
  
  // Manip DPad Right: Adjust shooting back +
  frc2::Button m_manDPadR{[&] {return m_manStick.GetPOV()==90;}};
  frc2::InstantCommand m_AdjustSpeedBackUp{[this] {robotConfig["shootingSpeedBack"]+=robotConfig["shootingSpeedShift"];} , {&m_shooter} };
  
  // Manip DPad Down: Adjust shooting front -
  frc2::Button m_manDPadD{[&] {return m_manStick.GetPOV()==180;}};
  frc2::InstantCommand m_AdjustSpeedFrontDown{[this] {robotConfig["shootingSpeedFront"]-=robotConfig["shootingSpeedShift"];} , {&m_shooter} };
  
  // Manip DPad Left: Adjust shooting back -
  frc2::Button m_manDPadL{[&] {return m_manStick.GetPOV()==270;}};
  frc2::InstantCommand m_AdjustSpeedBackDown{[this] {robotConfig["shootingSpeedBack"]-=robotConfig["shootingSpeedShift"];} , {&m_shooter} };
  
  // Manip Right Bumper: Log Shooting Position
  frc2::Button m_manRB{[&] {return m_manStick.GetRightBumper();}};
  frc2::InstantCommand m_LogPos{[this] {m_driveBase.writeToFile("Position Logged! Front: " + (std::to_string(robotConfig["shootingSpeedFront"])) + ", Back: " + (std::to_string(robotConfig["shootingSpeedBack"])) + " @" + (std::to_string(posID))); posID++; } , {&m_driveBase} };

  // Manip Right Trigger: Shoot
  frc2::Button m_manRT{[&] {return (0.5 < m_manStick.GetRightTriggerAxis());}};

  // Manip Left Bumper: Shoot with Limelight?
  frc2::Button m_manLB{[&] {return m_manStick.GetLeftBumper();}};

  // Manip Left Trigger: Shoot
  frc2::Button m_manLT{[&] {return (0.5 < m_manStick.GetLeftTriggerAxis());}};
  
  // Manip A: Collect With Intake
  frc2::Button m_manA{[&] {return m_manStick.GetAButton();}};

  // Manip B: Uncollect
  frc2::Button m_manB{[&] {return m_manStick.GetBButton();}};
  frc2::InstantCommand m_Uncollect{[this] {m_collector.SetMotorPO(-robotConfig["collectMoveSpeed"]); m_elevator.SetMotorPO(-robotConfig["elevatorMoveSpeed"]);} , {&m_collector, &m_elevator} };
  
  // Manip X: Swap Collector Up/Down
  frc2::Button m_manX{[&] {return m_manStick.GetXButton();}};
  frc2::InstantCommand m_CollectorSwap{[this] {m_collector.SwapLiftMotorPOHold();} , {&m_shooter} };
 
 /*
  // Manip Dpad Right: Center
  frc2::Button m_manDPadRight{[&] {return m_manStick.GetPOV()>=45 && m_manStick.GetPOV()<=135;}};
  */

  // Manip Y: Collect Without Intake
  frc2::Button m_manY{[&] {return m_manStick.GetYButton();}};

  // Manip Start: Swap Vision Target
  frc2::Button m_manStart{[&] {return m_manStick.GetStartButton();}};
  frc2::InstantCommand m_PipelineSwap{[this] {m_shooter.ChoosePipeline();} , {&m_shooter} };

  frc2::RunCommand m_NoShoot{[this] {m_shooter.SetMotorsPO(0, 0);}, {&m_shooter} };
  frc2::RunCommand m_NoCollect{[this] {m_collector.SetMotorPO(0);}, {&m_collector} };
  frc2::RunCommand m_NoElevate{[this] {m_elevator.SetMotorPO(0);}, {&m_elevator} };
  frc2::RunCommand m_ClimbControls{[this] {
    double m_turn   = m_manStick.GetRightX();
    double m_extend = m_manStick.GetLeftY();
    double passTurn   = (abs(m_turn*1000)   > 200?m_turn:0.0);
    double passExtend = (abs(m_extend*1000) > 200?m_extend:0.0);
    m_climber.SetMotorsPO(passTurn, passExtend);
    wpi::outs() << "Front: " << std::to_string((double) robotConfig["shootingSpeedFront"]) << " Back: " << std::to_string((double) robotConfig["shootingSpeedBack"]) << "\n";
  }, {&m_climber}};
  
  int command_no;
 
 private:
  frc::XboxController m_driverStick{0};
  frc::XboxController m_manStick{1};
  
  DriveBase m_driveBase;
  Shooter m_shooter;
  Climber m_climber;
  Collector m_collector;
  Elevator m_elevator;

  void ConfigureButtonBindings();

  std::vector<std::string> commands;
  std::fstream autofile;
  std::fstream configfile {"/home/lvuser/wcrj/config.txt"};
  std::string autofilename {"/home/lvuser/wcrj/autonomous.txt"};
  
  int posID;
};