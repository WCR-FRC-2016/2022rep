/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

std::map<std::string, double> robotConfig = {
    {"RampTime", 0.325},
    {"PIDDeadband", 0.114}, // TODO: PID needs to be tuned.
    {"minTurn", 0.1},
    {"driveMaxSpeed", 0.85},
    {"record", 0},
    {"aimingP", 1},
    {"aimingI", 0},
    {"aimingD", 0},
    {"LIDARm", 43254.71311},
    {"LIDARb", -8.92784},
    {"useCamera", 0},
    {"useLIDAR", 0},
    {"useLimelight", 0},
	{"useRumbleManip", 0},
	{"useRumbleDriver", 0},
    {"shootingSpeedFront", 0.5},
    {"shootingSpeedBack", 0.5},
    {"shootingSpeedLLFA", 0.0025},
    {"shootingSpeedLLFB", 0.03},
    {"shootingSpeedLLFC", 0.1},
    {"shootingSpeedLLBA", 0.0025},
    {"shootingSpeedLLBB", 0.03},
    {"shootingSpeedLLBC", 0.1},
	{"shootingSpeedShift", 0.1},
	 {"shootingSpeedError", 0.05},
    {"collectLiftSpeed", 0.01},
    {"collectMoveSpeed", -1},
    {"elevatorMoveSpeed", 0.5},
	{"rumbleManipStrength", 0},
	{"rumbleDriverStrength", 0}
};
// When we make the how-to for config options, don't forget autoFileName, which expects a string and thus isn't in this map.

RobotContainer::RobotContainer() {
   SetConfig();
    
   m_driveBase.SetDefaultCommand(ArcadeDrive(&m_driveBase, 
    [this] { return m_driverStick.GetRightX()*robotConfig["driveMaxSpeed"];} ,
    [this] { return -m_driverStick.GetLeftY()/1.5;}
   ));
   m_driveBase.SetRecording(&m_recording);

   if (robotConfig["useLIDAR"]>0) {
       LIDARTest(&m_recording).Schedule();
   }
   
   //m_Rumble.Schedule();
   //if (robotConfig["useRumbleDriver"]>0) m_DriverRumble.Schedule();

   m_shooter.SetDefaultCommand(m_NoShoot);

   m_climber.SetDefaultCommand(m_ClimbControls);
   
   m_collector.SetDefaultCommand(m_NoCollect);

   m_elevator.SetDefaultCommand(m_NoElevate);
   
   ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
   // Configure your button bindings here
   
	m_driverLT.WhenPressed(m_AdjustSpeedDown);
	m_driverRT.WhenPressed(m_AdjustSpeedUp);
	m_driverRB.WhenPressed(m_SwapSpeed);
	m_driverB.WhenPressed(m_ReverseDrive);
	
	m_manDPadU.WhenPressed(m_AdjustSpeedFrontUp);
	m_manDPadR.WhenPressed(m_AdjustSpeedBackUp);
	m_manDPadD.WhenPressed(m_AdjustSpeedFrontDown);
	m_manDPadL.WhenPressed(m_AdjustSpeedBackDown);
	m_manBack.WhenPressed(m_LogPos);

    //m_manET.WhileHeld(m_ManualShoot);
    m_manLT.WhileHeld(m_SpinUpShoot);
    m_manRT.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector, 0.1, 0.5));
    m_manLB.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector, 0.85, 0.8));
    m_manRB.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector, false));
    //m_manLB.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector));
    m_manA.WhileHeld(Collect(&m_collector, &m_elevator, true));
    m_manB.WhileHeld(m_Uncollect);
    m_manX.WhenPressed(m_CollectorSwap);
    m_manY.WhileHeld(Collect(&m_collector, &m_elevator, false));
    //m_manDPadRight.WhileHeld(Center(&m_driveBase, &m_shooter));
    m_manStart.WhenPressed(m_PipelineSwap);
    
   m_always.WhileHeld(m_Rumble);
}

void RobotContainer::ReadFile() {
   // Reset file to start.
   autofile.close();
   autofile.open(autofilename);

   commands.clear();

   // Read the file.
   std::string line;
   while (getline(autofile, line)) {
      commands.push_back(line);
   }
}

void RobotContainer::SetConfig() {
   wpi::outs() << "Reading file!\n";

   // Reset file to start.
   configfile.close();
   configfile.open("/home/lvuser/wcrj/config.txt");

   std::string line;
   //std::map<std::string,double>::iterator itr;
   while (getline(configfile, line)) {
      std::string name;
      double value;
      std::istringstream words (line);
      words >> name;
      if (name == "autoFileName") {
         words >> autofilename;
      } else {
         words >> value;
         //wpi::outs() << name << " " << value << "\n";
         
         // Write to variable
         robotConfig[name] = value;
      }
   }
}

void RobotContainer::OpenRecordingFile() {
   m_recording.OpenFile();
}

void RobotContainer::CloseRecordingFile() {
   m_recording.CloseFile();
}

void RobotContainer::Record() {
	m_recording.WriteLine();
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // Read the file

   std::string command = commands.at(command_no);
   command_no++;
   wpi::outs() << command << "\n";

   std::string verb;
   std::vector<double> args;
   std::istringstream words (command);
   words >> verb;
   double num;
   while (words >> num) {
      args.push_back(num);
   }
   
   if (args.size()==3) {
      return new ArcadeDrive(&m_driveBase, [this, args] {return args[0];}, [this, args] {return args[1];}, args[2]);
   } else if (args.size()==2) {
      return new frc2::ScheduleCommand(new Collect(&m_collector, &m_elevator, (args[0]>0), args[1]));
   } else if (args.size()==1) {
      return new Shoot(&m_shooter, &m_elevator, &m_collector, (args[0]>0)?0.8:0.1, 0.5, 2500);
   } else {
      return new AutoCommand(&m_driveBase, &m_shooter, &m_collector, &m_elevator, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
   }
   //return new ArcadeDrive(&m_driveBase, [this, args] {return args[0];}, [this, args] {return args[1];}, 1);
}