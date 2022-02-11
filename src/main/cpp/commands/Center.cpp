/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Center.h"
#include "RobotMap.h"

Center::Center(DriveBase* drivebase, Shooter* shooter) : pid{frc2::PIDController(robotConfig["aimingP"], robotConfig["aimingI"], robotConfig["aimingD"])}, m_drivebase{drivebase}, m_shooter{shooter}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({drivebase, shooter});
}

// Called when the command is initially scheduled.
void Center::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Center::Execute() {
  double rawRotation = m_shooter->GetLimelightX();

  double passRotation = pid.Calculate(rawRotation, 0);

  if (abs(passRotation*1000)<10) {passRotation = 0;}

  passRotation = std::clamp(passRotation, -1.0, 1.0);

  wpi::outs() << std::to_string(passRotation) << "\n";
  wpi::outs() << "TestOutput\n";
  
  m_drivebase->ArcadeDrive(passRotation, 0.0);
}

// Called once the command ends or is interrupted.
void Center::End(bool interrupted) {}

// Returns true when the command should end.
bool Center::IsFinished() { return true; }
