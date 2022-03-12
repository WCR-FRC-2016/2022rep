/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"
#include "RobotMap.h"
//#include <frc/RobotDrive.h>

Climber::Climber() {
	//wpi::outs() << "Climber constructed\n";
}

void Climber::ClimberInit() {
	//wpi::outs() << "Climber initialized\n";
    initialized = true;

    Extend = new WPI_TalonSRX (climberExtendDrive);
    Turn = new WPI_TalonSRX (climberTurnDrive);

    Extend->ConfigFactoryDefault();
    Turn->ConfigFactoryDefault();

    Extend->SetInverted(false);
    Turn->SetInverted(false);

    Extend->ConfigPeakCurrentLimit(50,0);
    Turn->ConfigPeakCurrentLimit(50,0);

    Extend->ConfigPeakCurrentDuration(1000,0);
    Turn->ConfigPeakCurrentDuration(1000,0);

/*
    Extend->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    Turn->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    */

    Extend->EnableCurrentLimit(true);
    Turn->EnableCurrentLimit(true);


    //PID BTW
    /*
    Extend->Config_kP(0, RightP, 0);
    Extend->Config_kI(0, RightI, 0);
    Extend->Config_kD(0, RightD, 0);
    Turn->Config_kP(0, LeftP, 0);
    Turn->Config_kI(0, LeftI, 0);
    Turn->Config_kD(0, LeftD, 0);
    */

    Extend->ConfigNominalOutputForward(NominalOutput, 0);
    Extend->ConfigNominalOutputReverse(-NominalOutput, 0);
    Turn->ConfigNominalOutputForward(NominalOutput, 0);
    Turn->ConfigNominalOutputReverse(-NominalOutput, 0);

/*
    Extend->SetSensorPhase(false);
    Turn->SetSensorPhase(false);
    */


    Extend->ConfigPeakOutputForward(MaxOutput, 0);
    Extend->ConfigPeakOutputReverse(-MaxOutput, 0);
    Turn->ConfigPeakOutputForward(MaxOutput, 0);
    Turn->ConfigPeakOutputReverse(-MaxOutput, 0);

    Extend->ConfigNeutralDeadband(robotConfig["PIDDeadband"], 0);
    Turn->ConfigNeutralDeadband(robotConfig["PIDDeadband"], 0);

/*
    Extend->SetSelectedSensorPosition(0,0,0);
    Turn->SetSelectedSensorPosition(0,0,0);
*/
}

void Climber::Periodic() {
  if (!initialized) {
		Climber::ClimberInit();
	}
}

void Climber::SetTurnPosition(double position) {
	Turn->Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);
}

void Climber::SetExtendPosition(double position) {
	Extend->Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);
}

void Climber::SetMotorsPO(double turnPO, double extendPO) {
    double passTurnPO = turnPO;
    if (passTurnPO>0 && !HallEffectSensor.Get()) passTurnPO=0;
	Turn->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, passTurnPO);
	Extend->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, extendPO);
}