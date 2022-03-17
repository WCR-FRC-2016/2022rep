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
    {"record", 0},
    {"aimingP", 1},
    {"aimingI", 0},
    {"aimingD", 0},
    {"LIDARm", 43254.71311},
    {"LIDARb", -8.92784},
    {"useCamera", 0},
    {"useLIDAR", 0},
    {"useLimelight", 0},
    {"shootingSpeedTLF", 4000},
    {"shootingSpeedTLB", 4000},
    {"shootingSpeedTHF", 8000},
    {"shootingSpeedTHB", 7000},
	 {"shootingSpeedError", 100},
    {"collectLiftSpeed", 0.01}
};

RobotContainer::RobotContainer() {
   SetConfig();
    
   m_driveBase.SetDefaultCommand(ArcadeDrive(&m_driveBase, 
    [this] { return m_driverStick.GetRightX()/2;} ,
    [this] { return -m_driverStick.GetLeftY()/1.5;}
   ));

   if (robotConfig["useLIDAR"]>0) {
       // TODO: Make this not make the robot not drive.
       m_driveBase.SetDefaultCommand(LIDARTest(&m_driveBase));
   }

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

    //m_manET.WhileHeld(m_ManualShoot);
    m_manLT.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector, robotConfig["shootingSpeedTHF"], robotConfig["shootingSpeedTHB"]));
    m_manRT.WhileHeld(Shoot(&m_shooter, &m_elevator, &m_collector, robotConfig["shootingSpeedTLF"], robotConfig["shootingSpeedTLB"]));
    m_manA.WhileHeld(Collect(&m_collector, &m_elevator));
    m_manB.WhileHeld(m_Uncollect);
    m_manX.WhenPressed(m_CollectorSwap);
    //m_manDPadRight.WhileHeld(Center(&m_driveBase, &m_shooter));
    m_manY.WhenPressed(m_PipelineSwap);
}

void RobotContainer::OpenDriveBaseFile() {
   m_driveBase.openFile();
}

void RobotContainer::CloseDriveBaseFile() {
   m_driveBase.closeFile();
}

void RobotContainer::ReadFile() {
   // Reset file to start.
   autofile.close();
   autofile.open(autofilename);

   // Read the file.
   std::string line;
   while (getline(autofile, line))
   {
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
   while (getline(configfile, line))
   {
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
   while (words >> num)
   {
      args.push_back(num);
   }

   if (args.size()==3)
   {
      return new ArcadeDrive(&m_driveBase, [this, args] {return args[0];}, [this, args] {return args[1];}, args[2]);
   }
   return new ArcadeDrive(&m_driveBase, [this, args] {return args[0];}, [this, args] {return args[1];}, 1);
}
