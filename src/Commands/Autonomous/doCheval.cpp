//doCheval.cpp
#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Defences/ChevDeFris.h>
#include <TuningValues.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/CollectorMove.h>

AutoBase *AutoBase::doCheval()
{
	AutoBase *cmd = new AutoBase("Autonomous-doCheval");
	cmd->AddSequential(new CollectorMove(1.0f));
	cmd->AddSequential(new DriveForward( 5 ,1.0));
	cmd->AddSequential(new CollectorMove(0.0f));
	cmd->AddSequential(new DriveForward( 1, 1.0f));
	cmd->AddParallel(new CollectorMove(1.0f));
	cmd->AddSequential(new DriveForward(3, 1.0f));
	return cmd;

}

