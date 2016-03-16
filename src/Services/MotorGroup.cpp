/*
 * MotorGroup.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: S-4020395
 */

#include <CANTalon.h>
#include <Services/Logger.h>
#include <Services/Motor.h>
#include <Services/MotorGroup.h>
#include <cstdio>
#include <iterator>
#include <vector>

float MotorGroup::getLastOutput() {
	return lastOutput;
}

float MotorGroup::getLastCurrent() {
	return lastOutput;
}

MotorGroup::MotorGroup(std::vector<Motor*> motorgroup) :
		motorList(motorgroup) {
	c = 0;
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

	for (; it != this->motorList.end(); it++) {
		/*if ((*it)->stoppedStartTime == 0) {
		 (*it)->talon->Set(output * (*it)->C);
		 }
		 (*it)->speed = output;*/
		if ((*it)->talon != NULL) {
			(*it)->talon->Set((output /** (*it)->C*/));
			//So we stop breaking the motor
		}
	}

}
