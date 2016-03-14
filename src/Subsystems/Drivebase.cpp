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

//only use if you know what you are doing
void Drivebase::setLeftSpeed(double speed1, double speed2, double speed3) {
	const bool allLarger = speed1 > 0 && speed2 > 0 && speed3 > 0;
	const bool allSame = speed1 == speed2 && speed2 == speed3;
	const bool allLess = speed1 < 0 && speed2 < 0 && speed3 < 0;
	if (allLarger || allSame || allLess) {
		MotorManager::getMotorManager()->setSpeed(DRIVEBASE_LEFTMOTOR_1_PORT,
				speed1);
		MotorManager::getMotorManager()->setSpeed(DRIVEBASE_LEFTMOTOR_2_PORT,
				speed2);
		MotorManager::getMotorManager()->setSpeed(DRIVEBASE_LEFTMOTOR_3_PORT,
				speed3);
	}
}

void Drivebase::setRightSpeed(double speed1, double speed2, double speed3) {
	const bool allLarger = speed1 > 0 && speed2 > 0 && speed3 > 0;
	const bool allSame = speed1 == speed2 && speed2 == speed3;
	const bool allLess = speed1 < 0 && speed2 < 0 && speed3 < 0;
	if (allLarger || allSame || allLess) {
		MotorManager::getMotorManager()->setSpeed(DRIVEBASE_RIGHTMOTOR_1_PORT,
				speed1);
		MotorManager::getMotorManager()->setSpeed(DRIVEBASE_RIGHTMOTOR_2_PORT,
				speed2);
		MotorManager::getMotorManager()->setSpeed(DRIVEBASE_RIGHTMOTOR_3_PORT,
				speed3);
	}
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

void Drivebase::setHold(bool state) {
	holding = state;
}
bool Drivebase::isHolding() {
	return holding;
}
