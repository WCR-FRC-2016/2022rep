/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Shooter.h"
#include "subsystems/Elevator.h"
#include "subsystems/Collector.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class Shoot
    : public frc2::CommandHelper<frc2::CommandBase, Shoot> {
 public:
  Shoot(Shooter* shooter, Elevator* elevator, Collector* collector, double frontSpeed, double backSpeed, double time);
  Shoot(Shooter* shooter, Elevator* elevator, Collector* collector, double frontSpeed, double backSpeed);
  Shoot(Shooter* shooter, Elevator* elevator, Collector* collector, bool useLimelight);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
private:
  Shooter* m_shooter;
  Elevator* m_elevator;
  Collector* m_collector;
  
  double m_frontSpeed;
  double m_backSpeed;

  double m_frontSign;
  double m_backSign;

  bool m_atSpeed;
  bool m_config;
  bool m_useLimelight;

  double m_time;
  double m_elapsed;

  bool m_two;
  double m_timer;
};
