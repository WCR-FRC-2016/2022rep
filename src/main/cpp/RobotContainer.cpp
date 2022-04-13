/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

#include <frc/smartdashboard/SmartDashboard.h>

std::map<std::string, double> robotConfig = {
    {"RampTime", 0.325},
    {"PIDDeadband", 0.114}, // TODO: PID needs to be tuned.
    {"minTurn", 0.1},
    {"driveMaxSpeed", 0.85},
    {"record", 0},
    {"aimingP", 0.005},
    {"aimingI", 0},
    {"aimingD", 0},
    {"aimingTarget", 0},
    {"aimingvP", 0.005},
    {"aimingvI", 0},
    {"aimingvD", 0},
    {"aimingvTarget", 0},
    {"autoTurnP", 0.01},
    {"autoTurnI", 0},
    {"autoTurnD", 0},
    {"autoTurnError", 0},
    {"LIDARm", 43254.71311},
    {"LIDARb", -8.92784},
    {"useCamera", 0},
    {"useLIDAR", 0},
    {"useLimelight", 0},
	{"useRumbleManip", 0},
	{"useRumbleDriver", 0},
   {"shootingSpinUpTime", 1000},
    {"shootingSpeedFront", 0.5},
    {"shootingSpeedBack", 0.5},
    {"shootingSpeedLF", 0.1},
    {"shootingSpeedLB", 0.5},
    {"shootingSpeedHF", 0.65},
    {"shootingSpeedHB", 0.55},
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

RobotContainer::RobotContainer() {
   SetConfig();
    
   m_driveBase.SetDefaultCommand(ArcadeDrive(&m_driveBase, 
    [this] { return m_driverStick.GetRightX()/2;} ,
    [this] { return -m_driverStick.GetLeftY()*robotConfig["driveMaxSpeed"];}
   ));
   m_driveBase.SetRecording(&m_recording);
   
   //m_Rumble.Schedule();
   //if (robotConfig["useRumbleDriver"]>0) m_DriverRumble.Schedule();

   m_shooter.SetDefaultCommand(m_NoShoot);
   m_shooter.SetRecording(&m_recording);

   m_climber.SetDefaultCommand(m_ClimbControls);
   
   m_collector.SetDefaultCommand(m_NoCollect);
   m_collector.SetRecording(&m_recording);

   m_elevator.SetDefaultCommand(m_NoElevate);
   m_elevator.SetRecording(&m_recording);

   // Add commands to the autonomous command chooser
   std::vector<std::string> autoVector {};

   // Totally not copied and pasted from Stack Overflow
   DIR *dir;
   struct dirent *ent;
   if ((dir = opendir ("/home/lvuser/wcrj")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
         autoVector.push_back(ent->d_name);
      }
      closedir (dir);
   } else {
      /* could not open directory */
      perror ("");
   }

   frc::SmartDashboard::PutStringArray("Auto List", autoVector);
   
   ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
   // Configure your button bindings here
   
	m_driverLT.WhenPressed(m_AdjustSpeedDown);
	m_driverRT.WhenPressed(m_AdjustSpeedUp);
	m_driverRB.WhenPressed(m_SwapSpeed);
	m_driverB.WhenPressed(m_ReverseDrive);
   
    m_driverX.WhenPressed(m_PipelineSwap);
    m_driverY.WhileHeld(Center(&m_driveBase, &m_shooter));
	
	m_manDPadU.WhenPressed(m_AdjustSpeedFrontUp);
	m_manDPadR.WhenPressed(m_AdjustSpeedBackUp);
	m_manDPadD.WhenPressed(m_AdjustSpeedFrontDown);
	m_manDPadL.WhenPressed(m_AdjustSpeedBackDown);
	m_manBack.WhenPressed(m_LogPos);

    //m_manET.WhileHeld(m_ManualShoot);
    m_manLT.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector, false));
    m_manRT.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector, robotConfig["shootingSpeedLF"], robotConfig["shootingSpeedLB"]));
    m_manLB.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector, 0.85, 0.8));
    m_manRB.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector, robotConfig["shootingSpeedHF"], robotConfig["shootingSpeedHB"]));
    //m_manLB.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector));
    m_manA.WhileHeld(Collect(&m_collector, &m_elevator, true));
    m_manB.WhileHeld(Uncollect(&m_collector, &m_elevator));
    m_manX.WhenPressed(m_CollectorSwap);
    m_manY.WhileHeld(Collect(&m_collector, &m_elevator, false));
    
   m_always.WhileHeld(m_Rumble);

   if (robotConfig["useLIDAR"]>0) {
       m_always.WhileHeld(LIDARTest(&m_recording));
   }
}

void RobotContainer::ReadFile() {
   // Reset file to start.
   autofile.close();
   autofile.open("/home/lvuser/wcrj/" + frc::SmartDashboard::GetString("Auto Selector", "autonomous.txt"));

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
      words >> value;
      //wpi::outs() << name << " " << value << "\n";
      
      // Write to variable
      robotConfig[name] = value;
   }

   m_driveBase.Reset();
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
   
   switch (verb[0]) {
      case 'd': // drive
         if (args.size()<3) {
            return new ArcadeDrive(&m_driveBase, [this, args] {return args[0];}, [this, args] {return args[1];}, 1);
         } else {
            return new ArcadeDrive(&m_driveBase, [this, args] {return args[0];}, [this, args] {return args[1];}, args[2]);
         }
         break;
      case 'c': // collect
         return new frc2::ScheduleCommand(new Collect(&m_collector, &m_elevator, (args[0]>0), args[1]));
         break;
      case 'u': // uncollect
         return new frc2::ScheduleCommand(new Uncollect(&m_collector, &m_elevator, args[0]));
         break;
      case 's': // shoot
         return new Shoot(&m_shooter, &m_elevator, &m_collector, (args[0]>0)?robotConfig["shootingSpeedHF"]:robotConfig["shootingSpeedLF"], (args[0]>0)?robotConfig["shootingSpeedHB"]:robotConfig["shootingSpeedLB"], 2500);
         break;
      case 't': // turn
         return new TurnCommand(&m_driveBase, args[0]);
         break;
      case 'r': // replay
		 return new AutoCommand(&m_driveBase, &m_shooter, &m_collector, &m_elevator, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
		 break;
      default:
         return new ArcadeDrive(&m_driveBase, [this] {return 0;}, [this] {return 0;}, 1);
         break;
   }
   //return new ArcadeDrive(&m_driveBase, [this, args] {return args[0];}, [this, args] {return args[1];}, 1);
}