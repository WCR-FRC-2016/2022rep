/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Recording.h"
#include "RobotMap.h"

Recording::Recording(std::string filename) {
	recordfile.open(filename);
}

Recording::Recording() {
	recordfile.open("/home/lvuser/wcrj/replay.txt");
}

void Recording::OpenFile(std::string filename) {
	if (!recordfile.is_open()) recordfile.open(filename);
}

void Recording::OpenFile() {
	if (!recordfile.is_open()) recordfile.open("/home/lvuser/wcrj/replay.txt");
}


void Recording::CloseFile() {
	if (recordfile.is_open()) recordfile.close();
}

void Recording::WriteToFile(std::string msg) {
	recordfile << msg;
}