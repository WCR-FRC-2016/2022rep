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
#include "subsystems/Shooter.h"
#include "subsystems/Collector.h"
#include "subsystems/Elevator.h"
#include "commands/Collect.h"
#include "commands/Uncollect.h"
#include "commands/Shoot.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoCommand
    : public frc2::CommandHelper<frc2::CommandBase, AutoCommand> {
 public:
  AutoCommand(DriveBase* drivebase, Shooter* shooter, Collector* collector, Elevator* elevator, double rotation, double forward, double front, double back, double collect, double shoot);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
private:
  DriveBase* m_drivebase;
  Shooter* m_shooter;
  Collector* m_collector;
  Elevator* m_elevator;

  Collect* m_Collect;
  Uncollect* m_Uncollect;
  Shoot* m_Shoot;

  double m_rotation;
  double m_forward;
  double m_front;
  double m_back;
  double m_collect;
  double m_shoot;
};
