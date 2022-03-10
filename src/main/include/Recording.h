/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <fstream>
#include <string>

class Recording {
 private:
  std::fstream recordfile;

 public:
  Recording(std::string filename);
  Recording();
  void OpenFile(std::string filename);
  void OpenFile();
  void CloseFile();
  void WriteToFile(std::string msg);
};
