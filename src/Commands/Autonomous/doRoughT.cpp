#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/CollectorMove.h>
#include <TuningValues.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");
	//cmd->AddSequential(new CollectorMove(cTOP));
	cmd->AddSequential(new DriveForward(5, 0.55));	//Reach the defence
	cmd->AddSequential(new DriveForward(8.5, 0.55));	//breach the defence
	return cmd;
}




