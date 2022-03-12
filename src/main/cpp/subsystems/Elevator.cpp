/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "RobotMap.h"
//#include <frc/RobotDrive.h>

Elevator::Elevator() {
	//wpi::outs() << "Elevator constructed\n";
}

void Elevator::ElevatorInit() {
	//wpi::outs() << "Elevator initialized\n";
    initialized = true;

    Motor = new WPI_TalonSRX (elevatorMotorDrive);
    
    Motor->ConfigFactoryDefault();
    
    Motor->SetInverted(false);
    
    Motor->ConfigPeakCurrentLimit(50,0);
    
    Motor->ConfigPeakCurrentDuration(1000,0);
    
/*
    Motor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
        */

    Motor->EnableCurrentLimit(true);

    Motor->ConfigNominalOutputForward(NominalOutput, 0);
    Motor->ConfigNominalOutputReverse(-NominalOutput, 0);

/*
    Motor->SetSensorPhase(false);
        */


    Motor->ConfigPeakOutputForward(MaxOutput, 0);
    Motor->ConfigPeakOutputReverse(-MaxOutput, 0);
    
    Motor->ConfigNeutralDeadband(robotConfig["PIDDeadband"], 0);
    
/*
    Motor->SetSelectedSensorPosition(0,0,0);
    */

	
	// Also figure out why it crashes the code on 2018 robot but not 2019.
    //_diffDrive->SetSafetyEnabled(false);

    //BackL->SetSafetyEnabled(false);
    //BackR->SetSafetyEnabled(false);
    //_diffDrive->SetExpiration(.5); TODO: Figure out what this does. Also figure out why it crashes the code on 2018 robot but not 2019.
}

void Elevator::Periodic() {
  if (!initialized) {
		Elevator::ElevatorInit();
	}
}

void Elevator::SetRecording(Recording* recording) {
	m_recording = recording;
}

void Elevator::SetMotorPO(double PO) {
	if (robotConfig["record"]>0)
	{
		m_recording->WriteData(6, PO);
	}
	
	Motor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, PO);
}

bool Elevator::GetSwitch() {
    return false;
}