/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Collector.h"
#include "RobotMap.h"
//#include <frc/RobotDrive.h>

Collector::Collector() {
	//wpi::outs() << "Collector constructed\n";
}

void Collector::CollectorInit() {
	//wpi::outs() << "Collector initialized\n";
    initialized = true;

    Motor = new WPI_TalonSRX (collectorMotorDrive);
    LiftMotor = new WPI_TalonSRX (collectorLiftMotorDrive);

    Motor->ConfigFactoryDefault();
    LiftMotor->ConfigFactoryDefault();

    Motor->SetInverted(false);
    LiftMotor->SetInverted(false);

    Motor->ConfigPeakCurrentLimit(50,0);
    LiftMotor->ConfigPeakCurrentLimit(50,0);

    Motor->ConfigPeakCurrentDuration(1000,0);
    LiftMotor->ConfigPeakCurrentDuration(1000,0);

/*
    Motor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    LiftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    */

    Motor->EnableCurrentLimit(true);
    LiftMotor->EnableCurrentLimit(true);

    Motor->ConfigNominalOutputForward(NominalOutput, 0);
    Motor->ConfigNominalOutputReverse(-NominalOutput, 0);
    LiftMotor->ConfigNominalOutputForward(NominalOutput, 0);
    LiftMotor->ConfigNominalOutputReverse(-NominalOutput, 0);

/*
    Motor->SetSensorPhase(false);
    LiftMotor->SetSensorPhase(false);
    */


    Motor->ConfigPeakOutputForward(MaxOutput, 0);
    Motor->ConfigPeakOutputReverse(-MaxOutput, 0);
    LiftMotor->ConfigPeakOutputForward(MaxOutput, 0);
    LiftMotor->ConfigPeakOutputReverse(-MaxOutput, 0);

    Motor->ConfigNeutralDeadband(robotConfig["PIDDeadband"], 0);
    LiftMotor->ConfigNeutralDeadband(robotConfig["PIDDeadband"], 0);

/*
    Motor->SetSelectedSensorPosition(0,0,0);
    LiftMotor->SetSelectedSensorPosition(0,0,0);
*/
}

void Collector::Periodic() {
  if (!initialized) {
		Collector::CollectorInit();
	}

	double passPO = LiftMotorPO;
	if (passPO<0 && HallEffectSensor1.Get()) passPO = 0;
	if (passPO>0 && HallEffectSensor2.Get()) passPO = 0;
    LiftMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, passPO);
}

void Collector::SetLiftMotorPOHold(double PO) {
	double passPO = PO;
	if (passPO<0 && HallEffectSensor1.Get()) passPO = 0;
	if (passPO>0 && HallEffectSensor2.Get()) passPO = 0;
	
	LiftMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, passPO);
    LiftMotorPO = PO;
}

void Collector::SetMotorPO(double PO) {
	Motor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, PO);
}