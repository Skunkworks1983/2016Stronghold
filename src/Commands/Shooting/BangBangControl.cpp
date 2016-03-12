#include <Commands/Shooting/BangBangControl.h>
#include <Subsystems/Shooter.h>
#include <cstdbool>

#define BANG_BANG_FULL 1.0
#define BANG_BANG_NONE 0.0
#define NO_ENCODER_SPEED .7

BangBangControl::BangBangControl(double desiredSpeed, double timeActivated) {
	Requires(shooter);
	this->desiredSpeed = desiredSpeed;
	this->timeActivated = timeActivated;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	currentSpeed = 0;
}

BangBangControl::~BangBangControl() {

}

void BangBangControl::Initialize() {
	SetTimeout(timeActivated);
}

void BangBangControl::Execute() {
	if (shooter->getShooterSpeed() != 0) {
		shooter->setShooterSpeed(
				currentSpeed < desiredSpeed ? BANG_BANG_FULL : BANG_BANG_NONE);
	} else {
		shooter->setShooterSpeed(NO_ENCODER_SPEED);
	}
}

bool BangBangControl::IsFinished() {
	return IsTimedOut();
}

void BangBangControl::Interrupted() {
	End();
}

void BangBangControl::End() {
	shooter->setShooterSpeed(0);
}
