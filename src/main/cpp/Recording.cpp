/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Recording.h"
#include "RobotMap.h"

Recording::Recording(std::string filename) {
	OpenFile(filename);
}

Recording::Recording() {
	OpenFile();
}

void Recording::OpenFile(std::string filename) {
	if (!recordfile.is_open()) recordfile.open(filename, std::ios_base::out | std::ios_base::trunc);
}

void Recording::OpenFile() {
	OpenFile("/home/lvuser/wcrj/replay.txt");
}


void Recording::CloseFile() {
	if (recordfile.is_open()) recordfile.close();
}

void Recording::WriteData(int index, double dat) {
	data[index] = dat;
}

void Recording::WriteLine() {
	if (!recordfile.is_open()) return;
	
	recordfile << "replay";
	for (unsigned int i=0; i<data.size(); i++) {
		recordfile << " " << (std::to_string(data[i]));
	}
	recordfile << "\n";
}