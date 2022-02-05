/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Test.h"

Test::Test(DriveBase* drivebase, std::function<double()> rotation, std::function<double()> forward) : m_drivebase{drivebase}, m_rotation{rotation}, m_forward{forward}  {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({drivebase});
}

// Called when the command is initially scheduled.
void Test::Initialize() {
   //wpi::outs() << "Debug Statement 4\n";
}

// Called repeatedly when this Command is scheduled to run
void Test::Execute() {
    wpi::outs() << "TEST!!!\n";
    //wpi::outs() << m_rotation() << " - " << m_forward() << "\n";
}

// Called once the command ends or is interrupted.
void Test::End(bool interrupted) {}

// Returns true when the command should end.
bool Test::IsFinished() { return false; }
