/*
 * MotorGroup.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: S-4020395
 */

#include <CANTalon.h>
#include <DriverStation.h>
#include <Services/MotorGroup.h>
#include <cstdbool>
#include <cstdio>
#include <iterator>
#include <RobotMap.h>

#define DRIVEBASE_MIN_OUTPUT .51
#define DRIVEBASE_MAX_OUTPUT .92

float DrivebaseMotorGroup::lastOutput = 0;

MotorGroup::MotorGroup(std::vector<Motor*> motorgroup) :
		motorList(motorgroup) {
	c = 0;
	brownoutCount = 0;
}

std::vector<Motor*> & MotorGroup::getMotorList() {
	return motorList;
}

MotorGroup::~MotorGroup() {
	for (unsigned i = 0; i < motorList.size(); i++) {
		delete motorList[i];
	}
	delete &motorList;
}

void MotorGroup::PIDWrite(float output) {
	std::vector<Motor*>::iterator it = motorList.begin();

	for (; it != motorList.end(); ++it) {
		/*if ((*it)->stoppedStartTime == 0) {
		 (*it)->talon->Set(output * (*it)->C);
		 }
		 (*it)->speed = output;*/

		if ((*it)->talon != NULL) {
			(*it)->talon->Set(
					((*it)->isReversed() ? -1 : 1) * output /** (*it)->C*/);
		}
	}
	//LOG_INFO("MotorGroup PIDWrite is not the problem");
}

DrivebaseMotorGroup::DrivebaseMotorGroup(std::vector<Motor*> motorgroup) :
		MotorGroup(motorgroup) {
	if (motorgroup.size() != 6) {
		throw;
	}
}

void DrivebaseMotorGroup::PIDWrite(float output) {
	//std::vector<Motor*> motorList = MotorGroup::getMotorList();
	std::vector<Motor*>::iterator it = motorList.begin();

	const float original = output;

	unsigned count = 0;
	for (; it != this->motorList.end(); it++) {
		/*if ((*it)->stoppedStartTime == 0) {
		 (*it)->talon->Set(output * (*it)->C);
		 }
		 (*it)->speed = output;*/
		if (count != 1 && count != 4) {
			if ((*it)->talon != NULL) {
				if (output < 0) {
					if (output > -DRIVEBASE_MIN_OUTPUT) {
						output = -DRIVEBASE_MIN_OUTPUT;
					}
				} else if(output > 0) {
					if (output < DRIVEBASE_MIN_OUTPUT) {
						output = DRIVEBASE_MIN_OUTPUT;
					}
				}else{
					//twiddle
				}
				if(output > DRIVEBASE_MAX_OUTPUT){
					output = DRIVEBASE_MAX_OUTPUT;
				}else if(output < -DRIVEBASE_MAX_OUTPUT){
					output = -DRIVEBASE_MAX_OUTPUT;
				}else{
					//twiddle
				}

				DrivebaseMotorGroup::lastOutput = output;

				//SmartDashboard::PutNumber("MotorPower", output);

				if (log_count++ > 3) {
					//LOG_INFO("OutputToDriveBase: %f original %f", output, original);
					log_count = 0;
				}

				(*it)->talon->Set(output);
				//So we stop breaking the motor
			}
		}
		count++;
	}
//LOG_INFO("DriveBaseMotorGroup PIDWrite is not the problem");

}
