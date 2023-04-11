/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoCommand.h"
#include "RobotMap.h"

AutoCommand::AutoCommand(DriveBase* drivebase, Shooter* shooter, Collector* collector, Elevator* elevator, double rotation, double forward, double front, double back, double collect, double shoot) : m_drivebase{drivebase}, m_shooter{shooter}, m_collector{collector}, m_elevator{elevator}, m_rotation{rotation}, m_forward{forward}, m_front{front}, m_back{back}, m_collect{collect}, m_shoot{shoot}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({drivebase, shooter});

  m_Collect = new Collect(m_collector, m_elevator, true);
  m_Uncollect = new Uncollect(m_collector, m_elevator);
  m_Shoot = new Shoot(m_shooter, m_elevator, m_collector, m_front, m_back);
}

// Called when the command is initially scheduled.
void AutoCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoCommand::Execute() {
  m_drivebase->ArcadeDrive(m_rotation, m_forward);
  if (m_collect>0 && !m_Collect->IsScheduled()) m_Collect->Schedule();
  if (m_collect<0 && !m_Uncollect->IsScheduled()) m_Uncollect->Schedule();
  if (m_collect==0 && m_Collect->IsScheduled()) m_Collect->Cancel();
  if (m_collect==0 && m_Uncollect->IsScheduled()) m_Uncollect->Cancel();

  if (m_shoot>0 && !m_Shoot->IsScheduled()) m_Shoot->Schedule();
  if (m_shoot==0 && m_Shoot->IsScheduled()) m_Shoot->Cancel();
}

// Called once the command ends or is interrupted.
void AutoCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoCommand::IsFinished() { return true; }