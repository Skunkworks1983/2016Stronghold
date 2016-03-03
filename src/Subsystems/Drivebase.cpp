#include <Commands/Driving/TankDrive.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>

Drivebase::Drivebase() :
		Subsystem("Drivebase") {
}

Drivebase::~Drivebase() {

}

void Drivebase::InitDefaultCommand() {
	SetDefaultCommand(new TankDrive());
}

void Drivebase::resetEncoder() {

}

float Drivebase::getRightDistance() {
	return SensorManager::getSensorManager()->GetEncoderPosition(
	DRIVEBASE_RIGHT_ENCODER_PORT);
}

float Drivebase::getLeftDistance() {
	return SensorManager::getSensorManager()->GetEncoderPosition(
			DRIVEBASE_LEFT_ENCODER_PORT);
}

void Drivebase::setLeftSpeed(double speed) {
	MotorManager::getMotorManager()->setSpeed(DRIVEBASE_LEFTMOTOR_1_PORT,
			speed);
	MotorManager::getMotorManager()->setSpeed(DRIVEBASE_LEFTMOTOR_2_PORT,
			speed);
	MotorManager::getMotorManager()->setSpeed(DRIVEBASE_LEFTMOTOR_3_PORT,
			speed);
}

void Drivebase::setRightSpeed(double speed) {
	MotorManager::getMotorManager()->setSpeed(DRIVEBASE_RIGHTMOTOR_1_PORT,
			speed);
	MotorManager::getMotorManager()->setSpeed(DRIVEBASE_RIGHTMOTOR_2_PORT,
			speed);
	MotorManager::getMotorManager()->setSpeed(DRIVEBASE_RIGHTMOTOR_3_PORT,
			speed);
}
