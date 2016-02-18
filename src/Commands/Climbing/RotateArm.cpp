#include <Commands/Climbing/RotateArm.h>
#include <Subsystems/Climber.h>

RotateArm::RotateArm(float rotateArmEncoderTicks, float speed, float currentArmPos)
{
	Requires(climber);
	this->rotateArmEncoderTicks = rotateArmEncoderTicks;
	this->armStartPos = 0;
	this->armSpeed = speed;
	this->currentArmPos = currentArmPos;
}

RotateArm::~RotateArm(){

}
// Called just before this Command runs the first time
void RotateArm::Initialize()
{
	this->rotateArmEncoderTicks = climber->getArmPos();
	climber->setArmSpeed(armSpeed);
}

// Called repeatedly when this Command is scheduled to run
void RotateArm::Execute()
{
	currentArmPos = climber->getArmSpeed();
	float totalTurn = currentArmPos - armStartPos;
	if(totalTurn < rotateArmEncoderTicks){
		climber->setArmSpeed(0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RotateArm::IsFinished()
{
	currentArmPos = climber->getArmSpeed();
	float totalTurn = currentArmPos - armStartPos;
	if(totalTurn < rotateArmEncoderTicks){
		climber->setArmSpeed(0);
		return true; }

	return false;
}

// Called once after isFinished returns true
void RotateArm::End()
{
	climber->setArmSpeed(0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateArm::Interrupted()
{
	End();
}
