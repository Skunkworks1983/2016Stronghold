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
}

BangBangControl::~BangBangControl() {

}

void BangBangControl::Initialize() {
	SetTimeout(timeActivated);
}

void BangBangControl::Execute() {
	currentSpeed = 0;
	unsigned workingEncoders = 0;
	if (shooter->getLeftShooterSpeed() > 0) {
		currentSpeed += shooter->getLeftShooterSpeed();
		workingEncoders++;
	}
	if (shooter->getRightShooterSpeed() > 0) {
		currentSpeed += shooter->getRightShooterSpeed();
		workingEncoders++;
	}
	if (workingEncoders != 0) {
		currentSpeed /= 2;
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
