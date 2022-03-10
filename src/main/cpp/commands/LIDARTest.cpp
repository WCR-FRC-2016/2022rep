/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LIDARTest.h"

LIDARTest::LIDARTest(DriveBase* drivebase, Recording* recording) : m_drivebase{drivebase}, m_recording{recording} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({drivebase});
  
  // Set up the input channel for the counter
  counter.SetUpSource(0);
  
  // Set the encoder to count pulse duration from rising edge to falling edge
  counter.SetSemiPeriodMode(true);
}

// Called when the command is initially scheduled.
void LIDARTest::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void LIDARTest::Execute() {
    m_recording->WriteToFile(std::to_string((double) counter.GetPeriod()));
    m_recording->WriteToFile(" ");
    m_recording->WriteToFile(std::to_string((double) counter.GetPeriod()*robotConfig["LIDARm"] + robotConfig["LIDARb"]));
    m_recording->WriteToFile("\n");
}

// Called once the command ends or is interrupted.
void LIDARTest::End(bool interrupted) {m_drivebase->closeFile();}

// Returns true when the command should end.
bool LIDARTest::IsFinished() { return false; }
