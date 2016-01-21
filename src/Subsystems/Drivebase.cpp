#include "Drivebase.h"
#include "../RobotMap.h"

Drivebase::Drivebase() :
		Subsystem("ExampleSubsystem")
{

}

void Drivebase::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Drivebase::setLeftSpeed(double speed) {

}

void Drivebase::setRightSpeed(double speed) {

}
float Drivebase::getLightSensorValue(){
	return 0.0;


}
// Put methods for controlling this subsystem
// here. Call these from Commands.
