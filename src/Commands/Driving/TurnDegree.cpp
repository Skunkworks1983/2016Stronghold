/*
 * TurnDegree.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: S-4032218
 */

#include <Commands/Driving/TurnDegree.h>
#include <PIDController.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <RobotMap.h>

TurnDegree::TurnDegree(double degree)
{
	P = 1./180;
	I = 0; //TODO: Tune for competition robot, currently tuned to totebot sorta
	D = 0;
	//this->speed = speed; Speed is not passed in, would be tricky to implement with PID
	this->degree = degree;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	ahrsDead = sensorManager->ahrsDead; //True if the ahrs (gyro) is non functional for the round
	initialYaw = sensorManager->getYaw();
	epsilon = 5;
}

TurnDegree::~TurnDegree()
{
}

void TurnDegree::Initialize()
{
	motorManager->enablePID(PID_ID_TURN_DEGREE, degree); //Fix ahrsDead in motormanger somehow
}

void TurnDegree::Execute()
{
	//All looping of PID is done by the pidController object
}

bool TurnDegree::IsFinished()
{
	return fabs((sensorManager->getYaw() - initialYaw) - degree) < epsilon;
}

void TurnDegree::End()
{
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
	motorManager->disablePID(PID_ID_TURN_DEGREE);
}

void TurnDegree::Interrupted()
{
	End();
}
