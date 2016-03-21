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

TurnDegree::TurnDegree(double degree) {
	P = 1. / 180;
	I = 0; //TODO: Tune for competition robot, currently tuned to totebot sorta
	D = 0;
	//this->speed = speed; Speed is not passed in, would be tricky to implement with PID
	this->degree = degree;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	initialYaw = 0.0;
	epsilon = 2;
}

TurnDegree::~TurnDegree() {
}

void TurnDegree::Initialize() {

	ahrsDead = sensorManager->ahrsDead; //True if the ahrs (gyro) is non functional for the round
	//initialYaw = sensorManager->getYaw();
	initialYaw =
			SensorManager::getSensorManager()->getSensor(SENSOR_GYRO_ID)->PIDGet();
	motorManager->enablePID(PID_ID_DRIVEBASE_ROT, degree + initialYaw); //Fix ahrsDead in motormanger somehow

	//double speed = .7;
	//drivebase->setLeftSpeed(speed);
	//drivebase->setRightSpeed(-speed);

	LOG_INFO("Initialize of TurnDegree, target yaw %f, current yaw %f", degree,
			initialYaw);
}

void TurnDegree::Execute() {
	char str[1024];

	//All looping of PID is done by the pidController object
	double l1 = MotorManager::getMotorManager()->getMotor(
	DRIVEBASE_LEFTMOTOR_1_PORT)->talon->Get();
	double l2 = MotorManager::getMotorManager()->getMotor(
	DRIVEBASE_LEFTMOTOR_2_PORT)->talon->Get();
	double l3 = MotorManager::getMotorManager()->getMotor(
	DRIVEBASE_LEFTMOTOR_3_PORT)->talon->Get();

	double r1 = MotorManager::getMotorManager()->getMotor(
	DRIVEBASE_RIGHTMOTOR_1_PORT)->talon->Get();
	double r2 = MotorManager::getMotorManager()->getMotor(
	DRIVEBASE_RIGHTMOTOR_2_PORT)->talon->Get();
	double r3 = MotorManager::getMotorManager()->getMotor(
	DRIVEBASE_RIGHTMOTOR_3_PORT)->talon->Get();
	double yaw =
			SensorManager::getSensorManager()->getSensor(SENSOR_GYRO_ID)->PIDGet();
	LOG_INFO("%f, %f, %f\t%f, %f, %f, yaw: %f", l1, l2, l3, r1, r2, r3, yaw);
}

bool TurnDegree::IsFinished() {
	if (fabs(
			SensorManager::getSensorManager()->getSensor(SENSOR_GYRO_ID)->PIDGet()
					- (initialYaw + degree)) < epsilon) {
		onCount++;
	} else {
		onCount = 0;
	}
	return onCount > 20;
}

void TurnDegree::End() {
	LOG_INFO("End Called on TurnDegree, target yaw %f, current yaw %f", degree,
			SensorManager::getSensorManager()->getSensor(SENSOR_GYRO_ID)->PIDGet());
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
	motorManager->disablePID(PID_ID_DRIVEBASE_ROT);
}

void TurnDegree::Interrupted() {
	End();
}
