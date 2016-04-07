/*
 * Motor.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: S-4020395
 */

#include <CANSpeedController.h>
#include <CANTalon.h>
#include <SensorBase.h>
#include <Services/Logger.h>
#include <Services/Motor.h>
#include <TuningValues.h>
#include <cmath>
#include <cstdio>
#include <RobotMap.h>
#include <Services/Logger.h>

Motor::Motor(Priority prioArg, int portArg, float maxCurrent,
		ESubsystem parentSubsystem, bool brownoutProtect, bool reversed) :
		reversed(reversed), maxCurrent(maxCurrent), parentSubsystem(
				parentSubsystem), brownoutProtect(brownoutProtect) {
	overCurrentStartTime = 0;
	stoppedStartTime = 0;
	port = portArg;
	speed = 0;
	motorPriority = prioArg;

	if (SensorBase::CheckPWMChannel(port)) {	//TODO: make sure this works
		talon = new CANTalon(port);
		talon->SetSafetyEnabled(false);
		talon->SetControlMode(CANTalon::kPercentVbus);
	} else {
		LOG_INFO("Talon assignment failed on Port %d", port);
	}
	C = 1;
}

bool Motor::isReversed() {
	return reversed;
}

bool Motor::isBrownoutProtect(){
	return brownoutProtect;
}

Motor::~Motor() {

}

void Motor::setSpeed(float speed) {
	//LOG_RECORD("PORT: %f SPEED: %f", port, speed);
	talon->Set(speed);
}

void Motor::setC(Priority priorityArg, float voltage) {

	if (motorPriority == PRIORITY_FIRST) {
		if (voltage > POWER_BROWNOUT_VOLTAGE + POWER_DRIVEBASE_VOLTAGE_WIDTH) {
			this->C = 1;
		} else {
			this->C = pow(
					(((voltage - POWER_BROWNOUT_VOLTAGE)
							/ (POWER_DRIVEBASE_VOLTAGE_WIDTH))), 2);
		}
	} else if (this->motorPriority >= priorityArg) {
		this->C = pow(
				(((voltage - POWER_BROWNOUT_VOLTAGE)
						/ (motorPriority * POWER_VOLTAGE_WIDTH))), 2);
	}

}

void Motor::setBrakeMode(bool brake){
	talon->ConfigNeutralMode(brake ? CANTalon::NeutralMode::kNeutralMode_Brake : CANTalon::NeutralMode::kNeutralMode_Coast);
}

