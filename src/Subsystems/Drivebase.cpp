#include <Commands/TankDrive.h>
#include <Subsystems/Drivebase.h>
#include <Subsystems/MotorManager.h>
#include <Subsystems/SensorManager.h>

Drivebase::Drivebase() :
		Subsystem("Drivebase") {
		motorManager = MotorManager::getMotorManager();
}


Drivebase::~Drivebase()
{

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

float Drivebase::getRightDistance(){
	return SensorManager::getSensorManager()->GetEncoderPosition(DRIVEBASE_RIGHTENCODER_PORT);
}

float Drivebase::getLeftDistance(){
	return SensorManager::getSensorManager()->GetEncoderPosition(DRIVEBASE_LEFTENCODER_PORT);

} //Maybe move to somewhere else. Not now -Eli

void Drivebase::setLeftSpeed(double speed) {


}

void Drivebase::setRightSpeed(double speed) {

}

