/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Center.h"
#include "RobotMap.h"

Center::Center(DriveBase* drivebase, Shooter* shooter) : pidh{frc2::PIDController(robotConfig["aimingP"], robotConfig["aimingI"], robotConfig["aimingD"])}, pidv{frc2::PIDController(robotConfig["aimingvP"], robotConfig["aimingvI"], robotConfig["aimingvD"])}, m_drivebase{drivebase}, m_shooter{shooter}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({drivebase, shooter});
}

// Called when the command is initially scheduled.
void Center::Initialize() {
	pidh.SetPID(robotConfig["aimingP"], robotConfig["aimingI"], robotConfig["aimingD"]);
	pidh.SetSetpoint(robotConfig["aimingTarget"]);
	pidh.SetTolerance(2.5);
  
	pidv.SetPID(robotConfig["aimingvP"], robotConfig["aimingvI"], robotConfig["aimingvD"]);
	pidv.SetSetpoint(robotConfig["aimingvTarget"]);
	pidv.SetTolerance(2.5);
  
  m_shooter->SetLimelightCamMode(0);
}

// Called repeatedly when this Command is scheduled to run
void Center::Execute() {
  double rawRotation = m_shooter->GetLimelightX();
  double rawForward = m_shooter->GetLimelightY();

  double passRotation = -pidh.Calculate(rawRotation);
  double passForward = pidv.Calculate(rawForward);

  passRotation = std::clamp(passRotation, -1.0, 1.0);
  passForward = std::clamp(passForward, -1.0, 1.0);
  
  if (pidh.AtSetpoint()) {
    m_drivebase->ArcadeDrive(0, passForward);
  } else {
    m_drivebase->ArcadeDrive(passRotation, 0);
  }
}

// Called once the command ends or is interrupted.
void Center::End(bool interrupted) {
	pidh.Reset();
  
  //m_shooter->SetLimelightCamMode(1);
}

// Returns true when the command should end.
bool Center::IsFinished() { return pidh.AtSetpoint(); }
