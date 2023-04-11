/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Uncollect.h"
#include "RobotMap.h"

Uncollect::Uncollect(Collector* collector, Elevator* elevator, double time) : m_collector{collector}, m_elevator{elevator}, m_time{time}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({collector, elevator});
}

Uncollect::Uncollect(Collector* collector, Elevator* elevator) : m_collector{collector}, m_elevator{elevator}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({collector, elevator});
  
  m_time = -1;
}

// Called when the command is initially scheduled.
void Uncollect::Initialize() {
  m_collector->WriteData(1);

  m_elapsed = 0;
}

// Called repeatedly when this Command is scheduled to run
void Uncollect::Execute() {
  m_collector->SetMotorPO(-robotConfig["collectMoveSpeed"]);
  m_elevator->SetMotorPO(-robotConfig["elevatorMoveSpeed"]);
  
  m_elapsed+=20;
}

// Called once the command ends or is interrupted.
void Uncollect::End(bool interrupted) {
  m_collector->WriteData(0);
}

// Returns true when the command should end.
bool Uncollect::IsFinished() { return (m_time==-1)?false:(m_elapsed>=m_time); }