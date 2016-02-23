//doCheval.cpp
#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Defences/ChevDeFris.h>
#include <TuningValues.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/CollectorMove.h>

AutoBase *AutoBase::doCheval()
{
	AutoBase*cmd = new AutoBase("Autonomous-doCheval");
	//cmd->AddSequential(new CollectorMove(FLOOR));
	cmd->AddSequential(new DriveForward( 5 ,1.0));
	//cmd->AddParallel(new CollectorMove(UP));
	cmd->AddSequential(new DriveForward(3, 1.0f));
	return cmd;

}

