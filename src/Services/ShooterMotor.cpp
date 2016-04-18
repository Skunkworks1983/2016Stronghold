/*
 * ShooterMotor.cpp
 *
 *  Created on: Mar 13, 2016
 *      Author: S-4020395
 */

#include <CANSpeedController.h>
#include <CANTalon.h>
#include <CommandBase.h>
#include <PIDController.h>
#include <RobotMap.h>
#include <Services/Motor.h>
#include <Services/MotorManager.h>
#include <Services/ShooterMotor.h>
#include <Subsystems/Shooter.h>
#include <cstdbool>

//#define SHOOTER_MOTOR_MAX_ACCELERATION .04	//working
#define SHOOTER_MOTOR_MAX_ACCELERATION .08

ShooterMotor::ShooterMotor(ShooterSide side, double p, double i, double d) :
		side(side) {
#if USE_CAN_PID
	switch (side) {
		case LEFT:
		talon = MotorManager::getMotorManager()->getMotor(
				SHOOTER_MOTOR_LEFT_PORT)->talon;
		talon->SetSensorDirection(true);
		break;
		case RIGHT:
		talon = MotorManager::getMotorManager()->getMotor(
				SHOOTER_MOTOR_RIGHT_PORT)->talon;
		break;
	}
	talon->SetControlMode(CANTalon::ControlMode::kSpeed);
	talon->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	talon->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	//talon->SetPIDSourceType(PIDSourceType::kRate);
	talon->SetClosedLoopOutputDirection(true);
#else
	controller = new PIDController(p, i, d, this, this);
#endif
	setPID(p, i, d);
	setpoint = 0.0;
}

ShooterMotor::~ShooterMotor() {
	delete controller;
}

float ShooterMotor::getOutputPercentage() {
#if USE_CAN_PID
	return talon->GetOutputVoltage();
	//return talon->Get();
#else
	return 0.0;
#endif
}

void ShooterMotor::PIDWrite(float output) {
#if USE_CAN_PID
	//do nothing because pid is ran on talon
#else
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
#endif
}

double ShooterMotor::PIDGet() {
#if USE_CAN_PID
	return talon->GetSpeed();
	//return talon->PIDGet();
#else

	switch (side) {
	case LEFT:
		lastSpeed = CommandBase::shooter->getLeftShooterSpeed();
		return CommandBase::shooter->getLeftShooterSpeed();
	case RIGHT:
		lastSpeed = CommandBase::shooter->getRightShooterSpeed();
		return CommandBase::shooter->getRightShooterSpeed();
	}
	return 0.0;
#endif
}

bool ShooterMotor::isEnabled() {
#if USE_CAN_PID
	return talon->IsEnabled();
#else
	return controller->IsEnabled();
#endif
}

double ShooterMotor::getError() {
#if USE_CAN_PID
	return talon->GetClosedLoopError();
#else
	return controller->GetError();
#endif
}

void ShooterMotor::Disable() {
#if USE_CAN_PID
	LOG_INFO("DISABLING %s %x", (this->side == LEFT ? "left" : "right"), talon);
	talon->ClearStickyFaults();
	talon->SetControlMode(CANTalon::ControlMode::kPercentVbus);
	talon->Set(0.0);
	talon->SetControlMode(CANTalon::ControlMode::kSpeed);
	talon->SetSetpoint(0.0);
	talon->Set(0.0);
	talon->Disable();
	talon->Reset();
#else
	controller->Disable();
	oldOutput = 0.0;
#endif

}

void ShooterMotor::Enable() {
#if USE_CAN_PID
	LOG_INFO("ENABLING %s %x", (this->side == LEFT ? "left" : "right"), talon);

	if (talon->GetControlMode() != CANTalon::ControlMode::kSpeed) {
		talon->SetControlMode(CANTalon::ControlMode::kSpeed);
	}
	talon->Enable();
	talon->EnableControl();
#else
	controller->Enable();
	switch (side) {
	case LEFT:
		oldOutput = CommandBase::shooter->getLeftShooterMotorPower();
		break;
	case RIGHT:
		oldOutput = CommandBase::shooter->getRightShooterMotorPower();
		break;
	}
#endif
}

void ShooterMotor::SetSetpoint(float setpoint) {
	if (setpoint != this->setpoint) {
		this->setpoint = setpoint;
	}
#if USE_CAN_PID
	setpoint = (setpoint * SHOOTER_ENCODER_TICKS_PER_REV) / 10;
	talon->Set(setpoint);
	talon->SetSetpoint(setpoint);
#else
	controller->SetSetpoint(setpoint);
	switch (side) {
	case LEFT:
		oldOutput = CommandBase::shooter->getLeftShooterMotorPower();
		break;
	case RIGHT:
		oldOutput = CommandBase::shooter->getRightShooterMotorPower();
		break;
	}
#endif
}

double ShooterMotor::getSetpoint() {
#if USE_CAN_PID
	return talon->GetSetpoint();
#else
	return controller->GetSetpoint();
#endif
}

void ShooterMotor::Reset() {
#if USE_CAN_PID
	talon->Reset();
#else
	controller->Reset();
	switch (side) {
	case LEFT:
		oldOutput = CommandBase::shooter->getLeftShooterMotorPower();
		break;
	case RIGHT:
		oldOutput = CommandBase::shooter->getRightShooterMotorPower();
		break;
	}
#endif
}

void ShooterMotor::setPID(float p, float i, float d) {
	LOG_INFO("SHOOTERMOTOR %s setPID to %f, %f, %f",
			(side == LEFT ? "left" : "right"), p, i, d);

#if USE_CAN_PID
	talon->SetPID(p, i, d);
#else
	controller->SetPID(p, i, d);
#endif
}
