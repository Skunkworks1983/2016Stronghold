#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/Driving/TurnDegree.h>
#include <Services/SensorManager.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doRoughT");
	return cmd;
}




