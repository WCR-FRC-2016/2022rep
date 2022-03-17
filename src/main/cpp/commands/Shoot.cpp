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
  AddRequirements({shooter, elevator, collector});

  m_useLimelight = false;
}

Shoot::Shoot(Shooter* shooter, Elevator* elevator, Collector* collector) : m_shooter{shooter}, m_elevator{elevator}, m_collector{collector}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({shooter, elevator, collector});

  m_useLimelight = true;
}

// Called when the command is initially scheduled.
void Shoot::Initialize() {
  m_shooter->SetLimelightCamMode(0);
  
  if (m_useLimelight) {
    double LLY = m_shooter->GetLimelightY();

    m_frontSpeed = robotConfig["shootingSpeedLLFA"]*LLY*LLY + robotConfig["shootingSpeedLLFB"]*LLY + robotConfig["shootingSpeedLLFC"];
    m_backSpeed = robotConfig["shootingSpeedLLBA"]*LLY*LLY + robotConfig["shootingSpeedLLBB"]*LLY + robotConfig["shootingSpeedLLBC"];
  } else {
    m_frontSpeed = robotConfig["shootingSpeedFront"];
    m_backSpeed = robotConfig["shootingSpeedBack"];
  }

  m_atSpeed = false;
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
    double front_err = (m_frontSpeed>0.2)?((1.2-m_frontSpeed)/10.0):0;
    double back_err = (m_backSpeed>0.2)?((1.2-m_backSpeed)/10.0):0;

    m_shooter->SetMotorsPO(-(m_frontSpeed+front_err), -(m_backSpeed+back_err));
    
    wpi::outs() << std::to_string((double) m_frontSpeed) << " " << std::to_string((double) m_backSpeed) << "\n";
    wpi::outs() << std::to_string((double) m_shooter->GetMotorSpeed(false)) << " " << std::to_string((double) m_shooter->GetMotorSpeed(true)) << "\n\n";
	
    if (m_shooter->GetMotorSpeed(false)>m_frontSpeed && m_shooter->GetMotorSpeed(true)>m_backSpeed) {
      m_atSpeed = true;
    }

    if (m_atSpeed) {
      m_elevator->SetMotorPO(robotConfig["elevatorMoveSpeed"]);
      m_collector->SetMotorPO(robotConfig["collectMoveSpeed"]);
    } else {
      m_elevator->SetMotorPO(0);
      m_collector->SetMotorPO(0);
    }
}

// Called once the command ends or is interrupted.
void Shoot::End(bool interrupted) {
  m_shooter->SetLimelightCamMode(1);
}

// Returns true when the command should end.
bool Shoot::IsFinished() { return false; }
