/*
 * TurnDegree.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: S-4032218
 */

#include <CANTalon.h>
#include <Commands/Driving/TurnDegree.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/Motor.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>
#include <cstdio>

#define TURN_DEGREE_ESPSILON 2.0

TurnDegree::TurnDegree(double degree, bool absolute) : absolute(absolute){
	P = 1. / 180.0;
	I = 1.0 / 3000.0; //TODO: Tune for competition robot, currently tuned to totebot sorta
	D = 1.0 / 360.0;
	//this->speed = speed; Speed is not passed in, would be tricky to implement with PID

	this->degree = degree;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	initialYaw = 0.0;
	ahrsDead = false;
}

TurnDegree::~TurnDegree() {
}

void TurnDegree::Initialize() {

	motorManager->getPID(PID_ID_DRIVEBASE_ROT)->Reset();

	if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() + degree > 360.0) {
		degree = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() + degree
				- 360.0;
	}
	if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() + degree < 0.0) {
		degree = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() + degree
				+ 360.0;
	}

	ahrsDead = sensorManager->ahrsDead; //True if the ahrs (gyro) is non functional for the round

	motorManager->enablePID(PID_ID_DRIVEBASE_ROT, degree + (absolute ? 0 : initialYaw)); //Fix ahrsDead in motormanger somehow

	LOG_INFO("Initialize of TurnDegree, target yaw %f, current yaw %f", degree,
			initialYaw);
}

void TurnDegree::Execute() {
	//All looping of PID is done by the pidController object
	const double l1 = motorManager->getMotor(
	DRIVEBASE_LEFTMOTOR_1_PORT)->talon->Get();
	const double l2 = motorManager->getMotor(
	DRIVEBASE_LEFTMOTOR_2_PORT)->talon->Get();
	const double l3 = motorManager->getMotor(
	DRIVEBASE_LEFTMOTOR_3_PORT)->talon->Get();

	const double r1 = motorManager->getMotor(
	DRIVEBASE_RIGHTMOTOR_1_PORT)->talon->Get();
	const double r2 = motorManager->getMotor(
	DRIVEBASE_RIGHTMOTOR_2_PORT)->talon->Get();
	const double r3 = motorManager->getMotor(
	DRIVEBASE_RIGHTMOTOR_3_PORT)->talon->Get();

	const double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	//LOG_INFO("%f, %f, %f\t%f, %f, %f, yaw: %f", l1, l2, l3, r1, r2, r3, yaw);
}

bool TurnDegree::IsFinished() {
	const double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	if (fabs(yaw - degree) < TURN_DEGREE_ESPSILON) {
		onCount++;
	} else {
		onCount = 0;
	}
	return onCount > 20;
}

void TurnDegree::End() {
	LOG_INFO("End Called on TurnDegree, target yaw %f, current yaw %f error %f", degree,
			sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet(), sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet());
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
	motorManager->disablePID(PID_ID_DRIVEBASE_ROT);
}

void TurnDegree::Interrupted() {
	End();
}
