/*
 * InputReader.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: S-4020395
 */

#include <stddef.h>
#include <Services/InputReader.h>
#include <Services/Logger.h>
#include <TuningValues.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

void InputReader::readPIDValues(string pid_id, float *p, float *i, float *d,
		string filename) {
	const string delimiter = ",";
	string line;
	ifstream myfile(filename.c_str());
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line.find(pid_id) == std::string::npos) {
				continue;
			}
			size_t pos = 0;
			string token;
			int c = 0;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				cout << token << endl;
				line.erase(0, pos + delimiter.length());
				if (c == 0) {

				} else if (c == 1) {
					(*p) = atof(token.c_str());
				} else if (c == 2) {
					(*i) = atof(token.c_str());
				}
				c++;
			}
			(*d) = atof(line.c_str());

			cout << line << endl;
		}
		myfile.close();
	}
}

std::string InputReader::getPIDStringID(unsigned id) {
	std::string pidstr;
	switch (id) {
	case PID_ID_SHOOTER_1:
		pidstr = "PID_ID_SHOOTER_1";
		break;
	case PID_ID_SHOOTER_2:
		pidstr = "PID_ID_SHOOTER_2";
		break;
	case PID_ID_COLLECTOR:
		pidstr = "PID_ID_COLLECTOR";
		break;
	case PID_ID_TURN_DEGREE_RIGHT:
		pidstr = "PID_ID_TURN_DEGREE_RIGHT";
		break;
	case PID_ID_TURN_DEGREE_LEFT:
		pidstr = "PID_ID_TURN_DEGREE_LEFT";
		break;
	case PID_ID_CAMERA:
		pidstr = "PID_ID_CAMERA";
		break;
	case PID_ID_ROLLER:
		pidstr = "PID_ID_ROLLER";
		break;
	case PID_ID_ARM:
		pidstr = "PID_ID_ARM";
		break;
	case PID_ID_WINCH:
		pidstr = "PID_ID_WINCH";
		break;
	case PID_ID_DRIVEBASE_LEFT:
		pidstr = "PID_ID_DRIVEBASE_LEFT";
		break;
	case PID_ID_DRIVEBASE_RIGHT:
		pidstr = "PID_ID_DRIVEBASE_RIGHT";
		break;
	case PID_ID_DRIVEBASE_ROT:
		pidstr = "PID_ID_DRIVEBASE_ROT";
		break;
	}
	return pidstr;
}
