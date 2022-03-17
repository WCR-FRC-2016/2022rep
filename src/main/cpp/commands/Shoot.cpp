/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Shoot.h"
#include "RobotMap.h"

Shoot::Shoot(Shooter* shooter, Elevator* elevator, Collector* collector, double frontSpeed, double backSpeed) : m_shooter{shooter}, m_elevator{elevator}, m_collector{collector}, m_frontSpeed{frontSpeed}, m_backSpeed{backSpeed}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({shooter, elevator});
}

// Called when the command is initially scheduled.
void Shoot::Initialize() {
  // TODO: temp to fix
  m_frontSpeed = robotConfig["shootingSpeedFront"];
  m_backSpeed = robotConfig["shootingSpeedBack"];
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
    double front, back;
    front = m_frontSpeed/17868.0;
    back = m_backSpeed/17868.0;
    
    m_shooter->SetMotorsPO(-front, -back);
    
    wpi::outs() << std::to_string((double) m_frontSpeed) << " " << std::to_string((double) m_backSpeed) << "\n";
    wpi::outs() << std::to_string((double) front) << " " << std::to_string((double) back) << "\n";
    wpi::outs() << std::to_string((double) m_shooter->GetMotorSpeed(false)) << " " << std::to_string((double) m_shooter->GetMotorSpeed(true)) << "\n\n";
	
    if (m_shooter->GetMotorSpeed(false)>m_frontSpeed && m_shooter->GetMotorSpeed(true)>m_backSpeed) {
      m_elevator->SetMotorPO(robotConfig["elevatorMoveSpeed"]);
      m_collector->SetMotorPO(robotConfig["collectMoveSpeed"]);
    } else {
      m_elevator->SetMotorPO(0);
      m_collector->SetMotorPO(0);
    }
}

// Called once the command ends or is interrupted.
void Shoot::End(bool interrupted) {}

// Returns true when the command should end.
bool Shoot::IsFinished() { return false; }
