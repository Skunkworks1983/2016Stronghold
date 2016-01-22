#include <Commands/TankDrive.h>
#include <RobotMap.h>
#include <Subsystems/Drivebase.h>
#include <Talon.h>

Drivebase::Drivebase() :
		Subsystem("Drivebase") {
	leftMotor1 = new Talon(DRIVEBASE_LEFTMOTOR_1_PORT);
	leftMotor2 = new Talon(DRIVEBASE_LEFTMOTOR_2_PORT);
	leftMotor3 = new Talon(DRIVEBASE_LEFTMOTOR_3_PORT);
	rightMotor1 = new Talon(DRIVEBASE_RIGHTMOTOR_1_PORT);
	rightMotor2 = new Talon(DRIVEBASE_RIGHTMOTOR_2_PORT);
	rightMotor3 = new Talon(DRIVEBASE_RIGHTMOTOR_3_PORT);
}

Drivebase::~Drivebase() {
	delete leftMotor1;
	delete leftMotor2;
	delete leftMotor3;
	delete rightMotor1;
	delete rightMotor2;
	delete rightMotor3;
}

void Drivebase::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new TankDrive());
}

void Drivebase::setLeftSpeed(double speed) {
	leftMotor1->Set(-speed);
	leftMotor2->Set(-speed);
	leftMotor3->Set(-speed);
}

void Drivebase::setRightSpeed(double speed) {
	rightMotor1->Set(speed);
	rightMotor2->Set(speed);
	rightMotor3->Set(speed);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivebase::resetEncoder()
{

}

float Drivebase::getRightDistance(){
	return 0; //TODO change this
}

float Drivebase::getLeftDistance(){
	return 0;
}
