/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Collect.h"
#include "RobotMap.h"

Collect::Collect(Collector* collector, Elevator* elevator, bool intakeLift, double time) : m_collector{collector}, m_elevator{elevator}, m_intakeLift{intakeLift}, m_time{time}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({collector, elevator});
}

Collect::Collect(Collector* collector, Elevator* elevator, bool intakeLift) : m_collector{collector}, m_elevator{elevator}, m_intakeLift{intakeLift}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({collector, elevator});
  
  m_time = -1;
}

// Called when the command is initially scheduled.
void Collect::Initialize() {
  // Lower Arm
  if (m_intakeLift) m_collector->SetLiftMotorPOHold(robotConfig["collectLiftSpeed"]);

  m_collector->WriteData(1);
  
  m_elapsed = 0;
}

// Called repeatedly when this Command is scheduled to run
void Collect::Execute() {
  m_collector->SetMotorPO((m_elevator->GetSwitch1() || m_elevator->GetSwitch2())?robotConfig["collectMoveSpeed"]:0);
  m_elevator->SetMotorPO(m_elevator->GetSwitch1()?robotConfig["elevatorMoveSpeed"]:0);
  
  m_elapsed+=20;
}

// Called once the command ends or is interrupted.
void Collect::End(bool interrupted) {
  // Raise Arm
  if (m_intakeLift) m_collector->SetLiftMotorPOHold(-robotConfig["collectLiftSpeed"]);

  m_collector->WriteData(0);
}

// Returns true when the command should end.
bool Collect::IsFinished() { return (m_time==-1)?false:(m_elapsed>=m_time); }
