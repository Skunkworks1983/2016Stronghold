#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/Driving/TurnDegree.h>
#include <Services/SensorManager.h>
#include <Commands/MultiTool/CollectorMove.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");

	//cmd->AddSequential(new CollectorMove(UP));
	cmd->AddSequential(new DriveForward(8, 1.0));
	return cmd;
}




