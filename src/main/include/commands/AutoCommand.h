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
  AutoCommand(DriveBase* drivebase, Shooter* shooter, Collector* collector, Elevator* elevator, double rotation, double forward, double front, double back, double cmotor, double cliftmotor, double emotor);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
private:
  DriveBase* m_drivebase;
  Shooter* m_shooter;
  Collector* m_collector;
  Elevator* m_elevator;
  double m_rotation;
  double m_forward;
  double m_front;
  double m_back;
  double m_cmotor;
  double m_cliftmotor;
  double m_emotor;
};
