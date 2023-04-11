/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnCommand.h"
#include "RobotMap.h"

TurnCommand::TurnCommand(DriveBase* drivebase, double angle) : m_pid{frc2::PIDController(robotConfig["autoTurnP"], robotConfig["autoTurnI"], robotConfig["autoTurnD"])}, m_drivebase{drivebase}, m_angle{angle}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({drivebase});
}

// Called when the command is initially scheduled.
void TurnCommand::Initialize() {
	m_pid.SetPID(robotConfig["autoTurnP"], robotConfig["autoTurnI"], robotConfig["autoTurnD"]);
	m_pid.SetSetpoint(m_angle);
	m_pid.SetTolerance(robotConfig["autoTurnError"], 0.1);
}

// Called repeatedly when this Command is scheduled to run
void TurnCommand::Execute() {
  double passTurn = m_pid.Calculate(m_drivebase->GetAngle());
  wpi::outs() << std::to_string((double) m_drivebase->GetAngle()) << " " << std::to_string((double) passTurn) << "\n";
  m_drivebase->ArcadeDrive(passTurn, 0);
}

// Called once the command ends or is interrupted.
void TurnCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnCommand::IsFinished() { return m_pid.AtSetpoint(); }
