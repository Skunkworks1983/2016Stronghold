/*
 * ShooterMotor.cpp
 *
 *  Created on: Mar 13, 2016
 *      Author: S-4020395
 */

#include <CommandBase.h>
#include <PIDController.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterMotor.h>
#include <cmath>

ShooterMotor::ShooterMotor(ShooterSide side, double p, double i, double d) :
		side(side) {
	controller = new PIDController(p, i, d, this, this);
}

ShooterMotor::~ShooterMotor() {
	delete controller;
}

void ShooterMotor::PIDWrite(float output) {
	oldOutput = std::fmax(std::fmin(1.0, oldOutput + output), 0.0);

	switch (side) {
	case LEFT:
		CommandBase::shooter->setLeftShooterSpeed(oldOutput);
		break;
	case RIGHT:
		CommandBase::shooter->setRightShooterSpeed(oldOutput);
		break;
	}

}

double ShooterMotor::PIDGet() {
	switch (side) {
	case LEFT:
		return CommandBase::shooter->getLeftShooterSpeed();
	case RIGHT:
		return CommandBase::shooter->getRightShooterSpeed();
	}
	return 0.0;
}

void ShooterMotor::Disable() {
	controller->Disable();
	CommandBase::shooter->setShooterSpeed(0.0);
	oldOutput = 0.0;
}

void ShooterMotor::Enable() {
	controller->Enable();
	switch (side) {
	case LEFT:
		oldOutput = CommandBase::shooter->getLeftShooterMotorPower();
		break;
	case RIGHT:
		oldOutput = CommandBase::shooter->getRightShooterMotorPower();
		break;
	}
}

void ShooterMotor::SetSetpoint(float setpoint) {
	this->setpoint = setpoint;
	controller->SetSetpoint(setpoint);
	switch (side) {
	case LEFT:
		oldOutput = CommandBase::shooter->getLeftShooterMotorPower();
		break;
	case RIGHT:
		oldOutput = CommandBase::shooter->getRightShooterMotorPower();
		break;
	}
}

void ShooterMotor::Reset() {
	controller->Reset();
	switch (side) {
	case LEFT:
		oldOutput = CommandBase::shooter->getLeftShooterMotorPower();
		break;
	case RIGHT:
		oldOutput = CommandBase::shooter->getRightShooterMotorPower();
		break;
	}
}
