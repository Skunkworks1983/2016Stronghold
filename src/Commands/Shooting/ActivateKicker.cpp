#include <Commands/Shooting/ActivateKicker.h>
#include <sys/time.h>
#include <Subsystems/Collector.h>
#include <Services/MotorManager.h>

ActivateKicker::ActivateKicker()
{
	timeOut = 0.5;
	collector = CommandBase::collector;
	motorManager = MotorManager::getMotorManager();
}

void ActivateKicker::Initialize()
{
	collector->setKickerSpeed(1);
	SetTimeout(timeOut);
}

void ActivateKicker::Execute()
{

}

bool ActivateKicker::IsFinished() {
return false;
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
