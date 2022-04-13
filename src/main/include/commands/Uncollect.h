/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Collector.h"
#include "subsystems/Elevator.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class Uncollect
    : public frc2::CommandHelper<frc2::CommandBase, Uncollect> {
 public:
  Uncollect(Collector* collector, Elevator* elevator, double time);
  Uncollect(Collector* collector, Elevator* elevator);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
private:
  Collector* m_collector;
  Elevator* m_elevator;
  
  bool m_intakeLift;
  
  double m_time;
  double m_elapsed;
};
