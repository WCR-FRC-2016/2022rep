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
    
    //table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
}

void Shooter::ShooterInit() {
	//wpi::outs() << "Shooter initialized\n";
    
	//table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	//frc::Shuffleboard::GetTab("Numbers").Add("Hood",yTurretMotor->GetSelectedSensorPosition());
	//nt::NetworkTableInstance::GetDefault().GetTable("dataTable");

    initialized = true;
}

void Shooter::Periodic() {
  if (!initialized) {
		Shooter::ShooterInit();
	}
}