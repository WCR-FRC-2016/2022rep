/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Collect.h"
#include "RobotMap.h"

Collect::Collect(Collector* collector, Elevator* elevator) : m_collector{collector}, m_elevator{elevator}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({collector, elevator});
}

// Called when the command is initially scheduled.
void Collect::Initialize() {
  // Lower Arm
  m_collector->SetLiftMotorPOHold(1);
}

// Called repeatedly when this Command is scheduled to run
void Collect::Execute() {
  m_collector->SetMotorPO(1);
  m_elevator->SetMotorPO(m_elevator->GetSwitch1()?0:1);
}

// Called once the command ends or is interrupted.
void Collect::End(bool interrupted) {
  // Raise Arm
  m_collector->SetLiftMotorPOHold(-1);
}

// Returns true when the command should end.
bool Collect::IsFinished() { return true; }
