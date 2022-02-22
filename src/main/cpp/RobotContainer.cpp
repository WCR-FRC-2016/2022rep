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
    {"LIDARb", -8.92784}
};

RobotContainer::RobotContainer() {
   //*
   m_driveBase.SetDefaultCommand(ArcadeDrive(&m_driveBase, 
    [this] { return m_driverStick.GetRightX()/2;} ,
    [this] { return -m_driverStick.GetLeftY()/1.5;}
   ));
   //*/

  //m_driveBase.SetDefaultCommand(LIDARTest(&m_driveBase));

   m_shooter.SetDefaultCommand(m_NoShoot);

   m_climber.SetDefaultCommand(m_ClimbControls);
   
   ConfigureButtonBindings();

   SetConfig();
}

void RobotContainer::ConfigureButtonBindings() {
   // Configure your button bindings here

    m_manET.WhileHeld(m_ManualShoot);
    m_manA.WhileHeld(Center(&m_driveBase, &m_shooter));
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
   file.close();
   file.open("/home/lvuser/wcrj/autonomous.txt");

   // Read the file.
   std::string line;
   while (getline(file, line))
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
      words >> value;
      //wpi::outs() << name << " " << value << "\n";

      // Write to variable
      robotConfig[name] = value;
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
