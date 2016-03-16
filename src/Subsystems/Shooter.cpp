#include <CANTalon.h>
#include <Commands/Command.h>
#include <DigitalInput.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/Motor.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Services/ShooterMotor.h>
#include <Subsystems/Shooter.h>
#include <TuningValues.h>
#include <cstdio>

#define SHOOTER_SPEED 54.0 - 2

Shooter::Shooter() :
		Subsystem("Shooter") {
	motorManager = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();

	left = new ShooterMotor(ShooterMotor::LEFT, p, i, d);
	right = new ShooterMotor(ShooterMotor::RIGHT, p, i, d);

	frontLimitSwitch = new DigitalInput(SHOOTER_FRONT_LIMIT_SWITCH_PORT);
	backLimitSwitch = new DigitalInput(SHOOTER_BACK_LIMIT_SWITCH_PORT);
	breakBeam = new DigitalInput(COLLECTOR_BREAK_BEAM_PORT);
}

Shooter::~Shooter() {

}

void Shooter::InitDefaultCommand() {

}

ShooterMotor *Shooter::getLeft() {
	return left;
}
ShooterMotor *Shooter::getRight() {
	return right;
}

void Shooter::setPID(float p, float i, float d) {
	this->p = p;
	this->i = i;
	this->d = d;
	left->setPID(p,i,d);
	right->setPID(p,i,d);
	char str[1024];
	sprintf(str, "setPID to %f, %f, %f", p,i,d);
	Logger::getLogger()->log(str, Info);
}

void Shooter::setUpToSpeed(bool upToSpeed) {
	this->upToSpeed = upToSpeed;
}

bool Shooter::isUpToSpeed() {
	//return getRightShooterSpeed() > SHOOTER_SPEED	&& getLeftShooterSpeed() > SHOOTER_SPEED;
	return upToSpeed;
}

float Shooter::getShooterSpeed() {
	float currentSpeed = 0;
	unsigned workingEncoders = 0;
	if (getLeftShooterSpeed() > 0) {
		currentSpeed += getLeftShooterSpeed();
		workingEncoders++;
	}
	if (getRightShooterSpeed() > 0) {
		currentSpeed += getRightShooterSpeed();
		workingEncoders++;
	}
	if (workingEncoders != 0) {
		currentSpeed /= 2;
	} else {
		currentSpeed = 0;
	}
	return currentSpeed;
}

void Shooter::registerCommand(Command *cmd) {
	if (lastCommand == NULL) {
		Logger::getLogger()->log("lastCommand = cmd", Debug);
		lastCommand = cmd;
	} else {
		if (lastCommand->IsRunning()) {
			lastCommand->Cancel();
		}
		lastCommand = cmd;
		Logger::getLogger()->log("After", Debug);
	}
	char str[1024];
	sprintf(str, "Command %d registered", cmd != NULL ? cmd->GetID() : -420);
	Logger::getLogger()->log(str, Debug);
}

void Shooter::deregisterCommand(Command *cmd) {
	char str[1024];
	sprintf(str, "Command %d DEREGISTERED", cmd != NULL ? cmd->GetID() : -420);
	Logger::getLogger()->log(str, Debug);
	if (lastCommand == cmd) {
		if (lastCommand != NULL) {
			if (lastCommand->IsRunning()) {
				lastCommand->Cancel();
			}
		}
	}
}

void Shooter::setRollerSpeed(rollerDirection direction, float speed) {
	switch (direction) {
	case KForward:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, speed);
		break;

	case KBackward:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, -speed);
		break;

	case KStop:
		motorManager->setSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT, 0.0);
		break;
	}
}

bool Shooter::getFrontSensor() {
	return frontLimitSwitch->Get();
}

bool Shooter::getBackSensor() {
	return backLimitSwitch->Get();
}

bool Shooter::getBreakBeam() {
	return breakBeam->Get();
}

void Shooter::setRotatorSpeed(float rotatorSpeed) {
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT, rotatorSpeed);
	motorManager->setSpeed(COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT, rotatorSpeed);
}

double Shooter::getRotatorPosition() {
	return sensorManager->getSensor(SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet();
}

float Shooter::getRotatorDegrees() {
	return SensorManager::getSensorManager()->getSensor(
	SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet()
			/ COLLECTOR_ROTATION_TICKS_PER_DEGREE;
}

void Shooter::setShooterSpeed(float speed) {
	setLeftShooterSpeed(speed);
	setRightShooterSpeed(speed);
}

void Shooter::setRightShooterSpeed(float speedRight) {
	MotorManager::getMotorManager()->getMotor(SHOOTER_MOTOR_1_PORT)->setSpeed(
			-speedRight);
}

void Shooter::setLeftShooterSpeed(float speedLeft) {
	MotorManager::getMotorManager()->getMotor(SHOOTER_MOTOR_2_PORT)->setSpeed(
			-speedLeft);
}

//rotation per second
float Shooter::getLeftShooterSpeed() {
	return 10 * (SensorManager::getSensorManager()->getSensor(
	SENSOR_SHOOTER_ENCODER_2_ID)->getSpeed() / SHOOTER_ENCODER_TICKS_PER_REV);
}

//rotation per second
float Shooter::getRightShooterSpeed() {
	return 10 * (SensorManager::getSensorManager()->getSensor(
	SENSOR_SHOOTER_ENCODER_1_ID)->getSpeed() / SHOOTER_ENCODER_TICKS_PER_REV);
}

float Shooter::getLeftShooterMotorPower() {
	return MotorManager::getMotorManager()->getMotor(SHOOTER_MOTOR_2_PORT)->talon->Get();
}

float Shooter::getRightShooterMotorPower() {
	return MotorManager::getMotorManager()->getMotor(SHOOTER_MOTOR_1_PORT)->talon->Get();
}
