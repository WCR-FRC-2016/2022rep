/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveBase.h"
#include "RobotMap.h"
//#include <frc/RobotDrive.h>

DriveBase::DriveBase() {
	//wpi::outs() << "DriveBase constructed\n";
}

void DriveBase::DriveBaseInit() {
	//wpi::outs() << "DriveBase initialized\n";
    initialized = true;

    FrontL = new WPI_TalonSRX (frontLeftDrive);
    FrontR = new WPI_TalonSRX (frontRightDrive);
    BackL = new WPI_TalonSRX (backLeftDrive);
    BackR = new WPI_TalonSRX (backRightDrive);
	_diffDrive = new frc::DifferentialDrive(*FrontL, *FrontR);
	//ahrs = new AHRS(frc::SPI::Port::kMXP);

    FrontR->ConfigFactoryDefault();
    FrontL->ConfigFactoryDefault();
    BackR->ConfigFactoryDefault();
    BackL->ConfigFactoryDefault();

    FrontR->SetInverted(false);
    FrontL->SetInverted(false);
    BackR->SetInverted(false);
    BackL->SetInverted(false);

    FrontR->ConfigPeakCurrentLimit(50,0);
    FrontL->ConfigPeakCurrentLimit(50,0);
    BackR->ConfigPeakCurrentLimit(50,0);
    BackL->ConfigPeakCurrentLimit(50,0);

    FrontR->ConfigPeakCurrentDuration(1000,0);
    FrontL->ConfigPeakCurrentDuration(1000,0);
    BackR->ConfigPeakCurrentDuration(1000,0);
    BackL->ConfigPeakCurrentDuration(1000,0);

    FrontL->ConfigOpenloopRamp(robotConfig["RampTime"], 0);
    FrontR->ConfigOpenloopRamp(robotConfig["RampTime"], 0);
    BackL->ConfigOpenloopRamp(robotConfig["RampTime"], 0);
    BackR->ConfigOpenloopRamp(robotConfig["RampTime"], 0);

    FrontR->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    FrontL->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);

    FrontR->EnableCurrentLimit(true);
    FrontL->EnableCurrentLimit(true);
    BackR->EnableCurrentLimit(true);
    BackL->EnableCurrentLimit(true);


    //PID BTW
    /*
    FrontR->Config_kP(0, RightP, 0);
    FrontR->Config_kI(0, RightI, 0);
    FrontR->Config_kD(0, RightD, 0);
    FrontL->Config_kP(0, LeftP, 0);
    FrontL->Config_kI(0, LeftI, 0);
    FrontL->Config_kD(0, LeftD, 0);
    */

    FrontR->ConfigNominalOutputForward(NominalOutput, 0);
    FrontR->ConfigNominalOutputReverse(-NominalOutput, 0);
    FrontL->ConfigNominalOutputForward(NominalOutput, 0);
    FrontL->ConfigNominalOutputReverse(-NominalOutput, 0);

    FrontR->SetSensorPhase(false);
    FrontL->SetSensorPhase(false);


    FrontR->ConfigPeakOutputForward(MaxOutput, 0);
    FrontR->ConfigPeakOutputReverse(-MaxOutput, 0);
    FrontL->ConfigPeakOutputForward(MaxOutput, 0);
    FrontL->ConfigPeakOutputReverse(-MaxOutput, 0);

    FrontR->ConfigNeutralDeadband(robotConfig["PIDDeadband"], 0);
    FrontL->ConfigNeutralDeadband(robotConfig["PIDDeadband"], 0);

    FrontR->SetSelectedSensorPosition(0,0,0);
    FrontL->SetSelectedSensorPosition(0,0,0);

    BackL->Set(ctre::phoenix::motorcontrol::ControlMode::Follower, frontLeftDrive);
    BackR->Set(ctre::phoenix::motorcontrol::ControlMode::Follower, frontRightDrive);
    //wpi::outs() << "Done setting up motor\n";

		
}
void DriveBase::ArcadeDrive(double xAxis, double yAxis) {
	//wpi::outs() << std::to_string( ahrs -> GetAngle()) << "\n";

	if (robotConfig["record"]>0)
	{
		recordfile << "replay " << xAxis << " " << yAxis << " 1\n";
	}
	
  	double parsedLeft;
	double parsedRight;
	double parsedX;
	double parsedY;

	double power = 2.3;

	//New stuff here for driver improvements.
	double minX = 0.65;
	double minY = 0.5;
	double ySlope = (1-minY)/(1);
	double xSlope = (minX-1)/(1);
	double XSC = 0;
	//Setting inputs to a power

	//YAxis setup to have a minimum value required to drive the Talon when the YAxis is not zero.
	/*		Yaxis Parsed
		|  /
		| /
	minY	|/
		|
	--------------------- YAxis Raw
		|
	       /| -minY
	      /	|
	     /	|
	*/ 
	//XAxis scaled to have a maximum value of 1 when the Yaxis is 0 and a minimum value of minX when the Y axis is 1. 

	/*	XSC
		|
1.0	    	|\
		| \
		|  \
		|   \
		|    \
		|     \
		|      \
		| 	\
      	    Minx|	 \
		|	 |\		
		|	 | \		
		|	 |  \	
		----------------YAxis
	   	0.0 	 1.0

	*/
	if (yAxis > 0) {
		yAxis = ySlope * yAxis + minY;
		XSC = xSlope * yAxis + 1.0;
		xAxis = xAxis * XSC;
	} 
	else if (yAxis < 0) {
		yAxis = ySlope * yAxis - minY;
		XSC = xSlope * -yAxis + 1.0;
		xAxis = xAxis * XSC;
	}
 


	parsedX = xAxis *speed; //pow((xAxis>0)?xAxis:-xAxis, power) * (xAxis / (xAxis>0)?xAxis:-xAxis);

	parsedY = pow((yAxis>0)?yAxis:-yAxis, power) * (yAxis / (yAxis>0)?yAxis:-yAxis) * driveConstant * speed;

	if (yAxis < 0)
	{
		//TO BE
		//FILLED IN
		//Turning Left?
		
			parsedLeft = parsedY - parsedX;
			parsedRight = parsedY + parsedX;
		
	}
	else
	{
			parsedLeft = parsedY - parsedX;
			parsedRight = parsedY + parsedX;
	}
	//wpi::outs() << "ArcadeDrive function mathematics " << parsedLeft << " " << parsedRight << "\n";
	_diffDrive->TankDrive(-parsedLeft, parsedRight, false);

}
void DriveBase::RampSwitch(bool rampOn) {
	double ramp = (rampOn)?robotConfig["RampTime"]:0;
	FrontL->ConfigOpenloopRamp(ramp, 0);
    FrontR->ConfigOpenloopRamp(ramp, 0);
   	BackL->ConfigOpenloopRamp(ramp, 0);
    BackR->ConfigOpenloopRamp(ramp, 0);

}
void DriveBase::Periodic() {
  if (!initialized) {
		DriveBase::DriveBaseInit();
		//wpi::outs() << "Debug Statement 7\n";
	}
	//wpi::outs() << "Debug Statement 6\n";
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void DriveBase::reverseDrive () {
	driveConstant = driveConstant * -1;
}

double DriveBase::getSpeed() {
	return speed;
}

void DriveBase::setSpeed(double newSpeed) {
	speed = std::clamp(newSpeed, 0.0, 1.0);
}

void DriveBase::openFile() {
	if (!recordfile.is_open()) recordfile.open("/home/lvuser/wcrj/replay.txt");
}

void DriveBase::closeFile() {
	if (recordfile.is_open()) recordfile.close();
}

void DriveBase::writeToFile(std::string msg) {
	recordfile << msg;
}