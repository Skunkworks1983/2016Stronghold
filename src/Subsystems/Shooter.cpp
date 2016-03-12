#include <DigitalInput.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Shooter.h>
#include <TuningValues.h>

Shooter::Shooter() :
		Subsystem("Shooter") {
	frontLimitSwitch = new DigitalInput(SHOOTER_FRONT_LIMIT_SWITCH_PORT);
	backLimitSwitch = new DigitalInput(SHOOTER_BACK_LIMIT_SWITCH_PORT);
	breakBeam = new DigitalInput(COLLECTOR_BREAK_BEAM_PORT);
}

Shooter::~Shooter() {

}

void Shooter::InitDefaultCommand() {

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
