#include "Drivebase.h"
#include "../RobotMap.h"
#include "WPILib.h"
#include "Commands/TankDrive.h"

Drivebase::Drivebase() :
		Subsystem("Drivebase") {
		motorManager = MotorManager::getMotorManager();
}

Drivebase::~Drivebase() {
}

void Drivebase::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new TankDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivebase::resetEncoder()
{

}

void Drivebase::setLeftSpeed(double speed) {
	motorManager->setLeftSpeed(speed);
}

void Drivebase::setRightSpeed(double speed) {
	motorManager->setRightSpeed(speed);
}

float Drivebase::getRightDistance(){
	return 0; //TODO change this
}

float Drivebase::getLeftDistance(){
	return 0;
} //Maybe move to somewhere else. Not now -Eli
