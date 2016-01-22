#include "MotorManager.h"
#include "../RobotMap.h"

MotorManager::MotorManager() :
		Subsystem("MotorManager")
{
	leftMotor1 = new IMotor(DRIVEBASE_LEFTMOTOR_1_PORT);
	leftMotor2 = new IMotor(DRIVEBASE_LEFTMOTOR_2_PORT);
	leftMotor3 = new IMotor(DRIVEBASE_LEFTMOTOR_3_PORT);
	rightMotor1 = new IMotor(DRIVEBASE_RIGHTMOTOR_1_PORT);
	rightMotor2 = new IMotor(DRIVEBASE_RIGHTMOTOR_2_PORT);
	rightMotor3 = new IMotor(DRIVEBASE_RIGHTMOTOR_3_PORT);
}

MotorManager::~MotorManager() {
	delete leftMotor1;
	delete leftMotor2;
	delete leftMotor3;
	delete rightMotor1;
	delete rightMotor2;
	delete rightMotor3;
}

void MotorManager::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void MotorManager::setLeftSpeed(double speed) {
	leftMotor1->Set(-speed);
	leftMotor2->Set(-speed);
	leftMotor3->Set(-speed);
}

void MotorManager::setRightSpeed(double speed) {
	rightMotor1->Set(speed);
	rightMotor2->Set(speed);
	rightMotor3->Set(speed);
}

MotorManager * MotorManager::getMotorManager() {
	static MotorManager motorManager;
	return &motorManager;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
