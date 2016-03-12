#include <Commands/Command.h>
#include <DigitalInput.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Shooter.h>
#include <TuningValues.h>
#include <cstdio>

Shooter::Shooter() :
		Subsystem("Shooter") {
	motorManager = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();

	frontLimitSwitch = new DigitalInput(SHOOTER_FRONT_LIMIT_SWITCH_PORT);
	backLimitSwitch = new DigitalInput(SHOOTER_BACK_LIMIT_SWITCH_PORT);
	breakBeam = new DigitalInput(COLLECTOR_BREAK_BEAM_PORT);
}

Shooter::~Shooter() {

}

void Shooter::InitDefaultCommand() {

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
	}else{
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
	MotorManager::getMotorManager()->setSpeed(SHOOTER_MOTOR_2_PORT, speedRight);
}

void Shooter::setLeftShooterSpeed(float speedLeft) {
	MotorManager::getMotorManager()->setSpeed(SHOOTER_MOTOR_1_PORT, speedLeft);
}

float Shooter::getLeftShooterSpeed() {
	return SensorManager::getSensorManager()->getSensor(
			SENSOR_SHOOTER_ENCODER_1_ID)->PIDGet();
}

float Shooter::getRightShooterSpeed() {
	return SensorManager::getSensorManager()->getSensor(
			SENSOR_SHOOTER_ENCODER_2_ID)->PIDGet();
}
