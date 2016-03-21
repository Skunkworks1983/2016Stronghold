#include <Commands/Tests/ReadPIDValues.h>
#include <Services/InputReader.h>
#include <Services/MotorManager.h>
#include <Services/PIDWrapper.h>
#include <string>

ReadPIDValues::ReadPIDValues(const unsigned PIDId) :
		PIDId(PIDId) {

}

// Called just before this Command runs the first time
void ReadPIDValues::Initialize() {
	float p = 0.0;
	float i = 0.0;
	float d = 0.0;

	MotorManager::getMotorManager()->getPID(PIDId)->Disable();	//make sure PID is off while changing values
	MotorManager::getMotorManager()->getPID(PIDId)->Reset();	//reset I accumulation

	std::string PID_id = InputReader::getPIDStringID(PIDId);
	InputReader::readPIDValues("test", &p, &i, &d, "test");
	InputReader::readPIDValues(PID_id, &p, &i, &d, PID_VALUES_FILENAME);	//replace pid values with values read from file
	MotorManager::getMotorManager()->getPID(PIDId)->SetPID(p, i, d);
}

// Called repeatedly when this Command is scheduled to run
void ReadPIDValues::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ReadPIDValues::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ReadPIDValues::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReadPIDValues::Interrupted() {

}
