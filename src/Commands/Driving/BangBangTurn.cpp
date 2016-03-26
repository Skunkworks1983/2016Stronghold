/*
 * BangBangTurn.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: S-4020395
 */

#include <Commands/Driving/BangBangTurn.h>
#include <Services/Sensor.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <RobotMap.h>
#include <cmath>

#define BANG_BANG_TURN_TOLERANCE 2

BangBangTurn::BangBangTurn(const double targetDegrees, bool absolute, float timeout) :
		targetDegrees(targetDegrees), absolute(absolute), timeout(timeout) {
	Requires(drivebase);
	sensorManager = SensorManager::getSensorManager();
}

BangBangTurn::~BangBangTurn() {

}

void BangBangTurn::Initialize() {

	if(timeout > 0.0){
		SetTimeout(timeout);
	}

	speed *= 12.7 / DriverStation::GetInstance().GetBatteryVoltage();

	if (absolute) {
		targetDegrees;
	} else {
		if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() + targetDegrees
				> 360.0) {
			targetDegrees += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet()
					- 360.0;
		}
		if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() + targetDegrees
				< 0.0) {
			targetDegrees += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet()
					+ 360.0;
		}
	}

	const double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	LOG_INFO("BangBangTurn initialized with target %f, current yaw %f",
			targetDegrees, yaw);

}

void BangBangTurn::Execute() {
	const double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	LOG_INFO("Yaw: %f", yaw);

	double error = yaw - targetDegrees;

	if (DriverStation::GetInstance().IsSysBrownedOut()) {
		speed = .35;
	}
	if (speed > 1) {
		speed = 1;
	}

	if (fabs(error) < 20) {
		speed *= (fabs(error) / (fabs(error) + 1));
	} else {
		speed *= 1.02;
	}

	if (speed < .35) {
		speed = .35;
	}

	if (error < 0) {
		drivebase->setLeftSpeed(speed);
		drivebase->setRightSpeed(-speed);
	} else {
		drivebase->setLeftSpeed(-speed);
		drivebase->setRightSpeed(speed);
	}
}

bool BangBangTurn::IsFinished() {
	const double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	if (fabs(yaw - targetDegrees) < BANG_BANG_TURN_TOLERANCE) {
		onCount++;
	} else {
		onCount = 0;
	}
	return IsTimedOut() || onCount > 20;
}

void BangBangTurn::End() {
	const double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
	const double error = yaw - targetDegrees;

	LOG_INFO("BangBangTurn Ended with Target %f yaw %f error %f", targetDegrees,
			yaw, error);
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
}

void BangBangTurn::Interrupted() {
	End();
}

