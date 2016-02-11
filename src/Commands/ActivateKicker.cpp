#include "ActivateKicker.h"

ActivateKicker::ActivateKicker()
{
	kickTime = 0;
	kickerActivated = false;
	kickerDone = false;
	collector = CommandBase::collector;
	motorManager = MotorManager::getMotorManager();


}
void ActivateKicker::Initialize()
{
	kickTime = 0;
	kickerActivated = false;
}

void ActivateKicker::Execute()
{
	if (kickerActivated == false){
		collector->setKickerSpeed(1);
		kickerActivated = true;
	} else {
		if (kickTime == 0){
			kickTime = clock();
		}
		if (clock() == kickTime + (CLOCKS_PER_SEC * 0.5)) {
			collector->setKickerSpeed(0);
			kickerDone = true;
		}
	}

}

bool ActivateKicker::IsFinished() {
	if (kickerDone == true) {
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void ActivateKicker::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ActivateKicker::Interrupted()
{

}
