#include <Commands/Shooting/BangBangControl.h>
#include <Services/Logger.h>
#include <Subsystems/Shooter.h>
#include <cstdbool>
#include <cstdio>

#define BANG_BANG_FULL .6
#define BANG_BANG_NONE .5
#define NO_ENCODER_SPEED .6

#define SCALING_CONSTANT .2

#define ERROR_SCALAR .0018

BangBangControl::BangBangControl(double targetSpeed, double timeOut) {
	Requires(shooter);
	this->targetSpeed = targetSpeed;
	this->timeOut = timeOut;
	realSpeed = 0.0;
}

BangBangControl::~BangBangControl() {
}

void BangBangControl::Initialize() {
	LOG_INFO("BangBangControl Initialize");
	realSpeed = .01;
	alreadyRamped = false;
	if (timeOut > 0) {
		SetTimeout(timeOut);
	}
	shooter->setShooterSpeed(realSpeed);
	leftSpeed = BANG_BANG_FULL;
	rightSpeed = BANG_BANG_FULL;
}

void BangBangControl::Execute() {
	if ((shooter->getLeftShooterSpeed() < targetSpeed * .25
			|| shooter->getRightShooterSpeed() < targetSpeed * .25)
			&& !alreadyRamped) {
		realSpeed *= (1.0 + SCALING_CONSTANT);
		shooter->setShooterSpeed(realSpeed);
	} else {
		realSpeed = BANG_BANG_FULL;
		alreadyRamped = true;
	}

	if (alreadyRamped) {
		double leftError = targetSpeed - shooter->getLeftShooterSpeed();
		double rightError = targetSpeed - shooter->getRightShooterSpeed();

		leftSpeed += leftError * ERROR_SCALAR;
		rightSpeed += rightError * ERROR_SCALAR;
		if (leftSpeed > 1.0) {
			leftSpeed = 1.0;
		}
		if (rightSpeed > 1.0) {
			rightSpeed = 1.0;
		}
		shooter->setLeftShooterSpeed(leftSpeed);
		shooter->setRightShooterSpeed(rightSpeed);
	}

	/*shooter->setLeftShooterSpeed(
	 shooter->getLeftShooterSpeed() < targetSpeed ?
	 realSpeed : BANG_BANG_NONE);
	 shooter->setRightShooterSpeed(
	 shooter->getRightShooterSpeed() < targetSpeed ?
	 realSpeed : BANG_BANG_NONE);*/
}

bool BangBangControl::IsFinished() {
	return IsTimedOut();
}

void BangBangControl::Interrupted() {
	End();
}

void BangBangControl::End() {
	LOG_INFO("BangBangControl ended");
	shooter->setShooterSpeed(0);
}
