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

#define DRIVEBASE_MIN_OUTPUT .4
#define DRIVEBASE_MAX_OUTPUT .84

#define SHOOTER_ROTATOR_RAMP_PER_TICK .10

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

ShooterRotatorGroup::ShooterRotatorGroup(std::vector<Motor*> motorgroup) :
		MotorGroup(motorgroup) {
	if (motorgroup.size() != 2) {
		throw;
	}
}

void ShooterRotatorGroup::PIDWrite(float output) {
	std::vector<Motor*>::iterator it = motorList.begin();

	if (fabs(output - realOutput) > SHOOTER_ROTATOR_RAMP_PER_TICK) {
		if (output < 0) {
			realOutput -= SHOOTER_ROTATOR_RAMP_PER_TICK;
		} else {
			realOutput += SHOOTER_ROTATOR_RAMP_PER_TICK;
		}
	} else {
		realOutput = output;
	}

	if(fabs(realOutput) > fabs(output)){
		realOutput = output;
	}

	if (output == 0) {
		realOutput = 0;
	}

	for (; it != this->motorList.end(); it++) {
		if ((*it)->talon != NULL) {
			(*it)->talon->Set(
					((*it)->isReversed() ? -1 : 1) * realOutput);
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
	std::vector<Motor*>::iterator it = motorList.begin();

	const float original = output;

	if (output < 0) {
		output =
				-1
						* (DRIVEBASE_MIN_OUTPUT
								+ fabs(output)
										* (DRIVEBASE_MAX_OUTPUT
												- DRIVEBASE_MIN_OUTPUT));
	} else if (output > 0) {
		output = DRIVEBASE_MIN_OUTPUT
				+ output * (DRIVEBASE_MAX_OUTPUT - DRIVEBASE_MIN_OUTPUT);
	} else {
		//don't move if trying to literally go zero
	}

	DrivebaseMotorGroup::lastOutput = output;

	unsigned count = 0;
	for (; it != this->motorList.end(); it++) {
		if ((*it)->talon != NULL) {
			(*it)->talon->Set(output);
		}
	}

	if (log_count++ > 3) {
		LOG_INFO("OutputToDriveBase: %f original %f", output, original);
		log_count = 0;
	}

	count++;
}
