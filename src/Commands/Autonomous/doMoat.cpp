#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/Driving/TurnDegree.h>
#include <Services/SensorManager.h>

AutoBase *AutoBase::doMoat()
{
	AutoBase *cmd = new AutoBase("Autonomous-doMoat");

	return cmd;
}
