#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/CollectorMove.h>
#include <TuningValues.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");
	cmd->AddSequential(new CollectorMove(cTOP));
	cmd->AddSequential(new DriveForward(REACH_DEFENCE_DISTANCE, REACH_DEFENCE_SPEED));
	return cmd;
}




