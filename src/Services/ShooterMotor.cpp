/*
 * ShooterMotor.cpp
 *
 *  Created on: Mar 13, 2016
 *      Author: S-4020395
 */

#include <CommandBase.h>
#include <PIDController.h>
#include <Services/Logger.h>
#include <Services/ShooterMotor.h>
#include <Subsystems/Shooter.h>
#include <cmath>
#include <cstdio>

#define SHOOTER_MOTOR_MAX_ACCELERATION .04

ShooterMotor::ShooterMotor(ShooterSide side, double p, double i, double d) :
		side(side) {
	controller = new PIDController(p, i, d, this, this);
	setpoint = 0.0;
}

ShooterMotor::~ShooterMotor() {
	delete controller;
}

void ShooterMotor::PIDWrite(float output) {
	output = std::fmax(-SHOOTER_MOTOR_MAX_ACCELERATION,
			std::fmin(output, SHOOTER_MOTOR_MAX_ACCELERATION));

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

double ShooterMotor::getSetpoint() {
	return controller->GetSetpoint();
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

void ShooterMotor::setPID(float p, float i, float d) {
	controller->SetPID(p, i, d);
	char str[1024];
	sprintf(str, "SHOOTERMOTOR setPID to %f, %f, %f", p, i, d);
	Logger::getLogger()->log(str, Info);
}
