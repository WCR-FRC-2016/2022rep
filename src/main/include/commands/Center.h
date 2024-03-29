/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "frc/controller/PIDController.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Shooter.h"

#include <string>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class Center
    : public frc2::CommandHelper<frc2::CommandBase, Center> {
 public:
  Center(DriveBase* drivebase, Shooter* shooter);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  frc2::PIDController pidh;
  frc2::PIDController pidv;
private:
  DriveBase* m_drivebase;
  Shooter* m_shooter;
};
