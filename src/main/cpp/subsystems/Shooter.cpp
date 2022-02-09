/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include "RobotMap.h"

Shooter::Shooter() {
	//wpi::outs() << "Shooter constructed\n";
    
    table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
}

void Shooter::ShooterInit() {
	//wpi::outs() << "Shooter initialized\n";
    
	table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	//frc::Shuffleboard::GetTab("Numbers").Add("Hood",yTurretMotor->GetSelectedSensorPosition());
	nt::NetworkTableInstance::GetDefault().GetTable("dataTable");

    initialized = true;

    Front = new WPI_TalonSRX (shooterFrontDrive);
    Back = new WPI_TalonSRX (shooterBackDrive);

    Front->ConfigFactoryDefault();
    Back->ConfigFactoryDefault();

    Front->SetInverted(false);
    Back->SetInverted(false);

    Front->ConfigPeakCurrentLimit(50,0);
    Back->ConfigPeakCurrentLimit(50,0);

    Front->ConfigPeakCurrentDuration(1000,0);
    Back->ConfigPeakCurrentDuration(1000,0);

	/*
    Front->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    Back->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
	*/

    Front->EnableCurrentLimit(true);
    Back->EnableCurrentLimit(true);


    //PID BTW
    /*
    Front->Config_kP(0, LeftP, 0);
    Front->Config_kI(0, LeftI, 0);
    Front->Config_kD(0, LeftD, 0);
    Back->Config_kP(0, RightP, 0);
    Back->Config_kI(0, RightI, 0);
    Back->Config_kD(0, RightD, 0);
    */

    Front->ConfigNominalOutputForward(NominalOutput, 0);
    Front->ConfigNominalOutputReverse(-NominalOutput, 0);
    Back->ConfigNominalOutputForward(NominalOutput, 0);
    Back->ConfigNominalOutputReverse(-NominalOutput, 0);

	/*
    Front->SetSensorPhase(false);
    Back->SetSensorPhase(false);
	*/

    Front->ConfigPeakOutputForward(MaxOutput, 0);
    Front->ConfigPeakOutputReverse(-MaxOutput, 0);
    Back->ConfigPeakOutputForward(MaxOutput, 0);
    Back->ConfigPeakOutputReverse(-MaxOutput, 0);

    Front->ConfigNeutralDeadband(robotConfig["PIDDeadband"], 0);
    Back->ConfigNeutralDeadband(robotConfig["PIDDeadband"], 0);

	/*
    Front->SetSelectedSensorPosition(0,0,0);
    Back->SetSelectedSensorPosition(0,0,0);
	*/
}

void Shooter::SetMotorsPO (double left, double right) {
	Front->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, left);
	Back->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, right);
}

void Shooter::ChoosePipeline() {
    int pipeline = 2; // Tape pipeline

    if (table->GetNumber("pipeline",0)==2) {
        pipeline = (frc::DriverStation::GetAlliance() == frc::DriverStation::kRed)?1:0; // Red/Blue pipelines, resp.
    }

    table->PutNumber("pipeline", pipeline);
}

double Shooter::GetLimelightX () {
    return table->GetNumber("tx", 0.0);
}

void Shooter::Periodic() {
  if (!initialized) {
		Shooter::ShooterInit();
	}
}