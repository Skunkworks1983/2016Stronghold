/*
 * TurnDegree.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: S-4032218
 */
#include "TurnDegree.h"


TurnDegree::TurnDegree(double degree)
{
	P = 0.0075;
	I = 0; //TODO: Tune for competition robot, currently tuned to totebot sorta
	D = 0;
	this->degree = degree;
	//this->speed = speed; Speed is not passed in, would be tricky to implement with PID
	sensorManager = SensorManager::getSensorManager();
	pidController = new PIDController(P, I, D, this, this);
	motorManager = MotorManager::getMotorManager();
	ahrsDead = sensorManager->ahrsDead; //True if the ahrs (gyro) is non functional for the round
	pidController->SetAbsoluteTolerance(1.0f);
}

TurnDegree::~TurnDegree()
{
}

void TurnDegree::Initialize()
{
	if(ahrsDead) {
		pidController->SetSetpoint(ENCODER_TURN_RADIUS_RATIO*degree);
		pidController->Enable();
		drivebase->resetEncoder();
	} else {
		pidController->SetSetpoint(sensorManager->getYaw() + degree);
		pidController->Enable();
	}
}

void TurnDegree::Execute()
{
	//All looping of PID is done by the pidController object
}

bool TurnDegree::IsFinished()
{
	if(ahrsDead) {
		if (drivebase->getLeftDistance() >= (degree * ENCODER_TURN_RADIUS_RATIO)) {
			return true;
		}
		else{
			return false;
		}
	} else {
		return pidController->OnTarget();
	}
}

void TurnDegree::End()
{
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
	pidController->Disable();
}

void TurnDegree::Interrupted()
{
	End();
}

double TurnDegree::PIDGet() {
	if(ahrsDead) {
		return drivebase->getLeftDistance();
	} else {
		return sensorManager->getYaw();
	}
}

void TurnDegree::PIDWrite(float output) {
	drivebase->setLeftSpeed(output);
	drivebase->setRightSpeed(output);
}
