/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <fstream>
#include <string>

// data indices:
//  0 - Drivebase turn
//  1 - Drivebase forward
//  2 - Shooter speed front
//  3 - Shooter speed back
//  4 - Collector in/out
//  5 - Collector lift
//  6 - Elevator in/out


//  9 - LIDAR distance raw
// 10 - LIDAR distance parsed

class Recording {
 private:
  std::fstream recordfile;
  
  double[11] data;

 public:
  Recording(std::string filename);
  Recording();
  void OpenFile(std::string filename);
  void OpenFile();
  void CloseFile();
  void WriteData(int index, double dat);
  void WriteLine();
};
