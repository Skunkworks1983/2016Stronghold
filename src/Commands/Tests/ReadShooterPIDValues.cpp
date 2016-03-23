#include <Commands/Tests/ReadShooterPIDValues.h>
#include <Services/InputReader.h>
#include <Services/ShooterMotor.h>
#include <Subsystems/Shooter.h>

#define SHOOTERPIDFILENAME "/U/shootervalues"

ReadShooterPIDValues::ReadShooterPIDValues(){

}

// Called just before this Command runs the first time
void ReadShooterPIDValues::Initialize() {
	float p = 0.0;
	float i = 0.0;
	float d = 0.0;

	shooter->getRight()->Disable();
	shooter->getLeft()->Disable();
	shooter->getLeft()->Reset();//reset I accumulation
	shooter->getRight()->Reset();//reset I accumulation

	InputReader::readPIDValues("SHOOTER_MOTORS", &p, &i, &d, SHOOTERPIDFILENAME);//replace pid values with values read from file
	shooter->setPID(p, i, d);
}

// Called repeatedly when this Command is scheduled to run
void ReadShooterPIDValues::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ReadShooterPIDValues::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ReadShooterPIDValues::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReadShooterPIDValues::Interrupted() {

}
