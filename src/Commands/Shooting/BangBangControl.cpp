#include "BangBangControl.h"

BangBangControl::BangBangControl(double desiredSpeed, double timeActivated) {
	this->desiredSpeed = desiredSpeed;
	this->timeActivated = timeActivated;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	currentSpeed = sensorManager->GetSpeed(SHOOTER_1_ENCODER_PORT);
}

BangBangControl::~BangBangControl() {

}

void BangBangControl::Initialize() {

	SetTimeout(timeActivated);
}

void BangBangControl::Execute() {
	while (currentSpeed < desiredSpeed) {
	motorManager->setSpeed(SHOOTER_MOTOR_1_PORT, 1);
	motorManager->setSpeed(SHOOTER_MOTOR_2_PORT, 1);
	}
	while (currentSpeed >= desiredSpeed) {
	motorManager->setSpeed(SHOOTER_MOTOR_1_PORT, 0);
	motorManager->setSpeed(SHOOTER_MOTOR_2_PORT, 0);
	}
}

bool BangBangControl::IsFinished() {
return false;
}

void BangBangControl::Interrupted() {

}

void BangBangControl::End() {

}
