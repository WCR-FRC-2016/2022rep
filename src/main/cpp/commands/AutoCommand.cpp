/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoCommand.h"
#include "RobotMap.h"

AutoCommand::AutoCommand(DriveBase* drivebase, Shooter* shooter, rotation, forward, front, back) : m_drivebase{drivebase}, m_shooter{shooter}, m_rotation{rotation}, m_forward{forward}, m_front{front}, m_back{back}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({drivebase, shooter});
}

// Called when the command is initially scheduled.
void AutoCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoCommand::Execute() {
  m_drivebase->ArcadeDrive(m_rotation, m_forward);
  m_shooter->SetMotorsPO(m_front, m_back);
}

// Called once the command ends or is interrupted.
void AutoCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoCommand::IsFinished() { return true; }