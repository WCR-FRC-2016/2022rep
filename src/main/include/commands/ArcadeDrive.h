/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/DriveBase.h"

#include <string>
#include <fstream>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ArcadeDrive
    : public frc2::CommandHelper<frc2::CommandBase, ArcadeDrive> {
 public:
  ArcadeDrive(DriveBase* drivebase, std::function<double()> rotation, std::function<double()> forward);
  ArcadeDrive(DriveBase* drivebase, std::function<double()> rotation, std::function<double()> forward, double time);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
private:
  DriveBase* m_drivebase;
  std::function<double()> m_rotation;
  std::function<double()> m_forward;
  double m_time;
  double m_elapsed;
};
