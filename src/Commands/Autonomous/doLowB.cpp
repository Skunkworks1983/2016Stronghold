#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/Driving/TurnRightEncoder.h>
#include <Commands/MultiTool/ActivateRollers.h>
#include <Commands/MultiTool/CollectorMove.h>
#include <Subsystems/Collector.h>
#include <iostream>

AutoBase *AutoBase::doLowB()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doLowB");
	//cmd->AddSequential(new CollectorMove(cLowBar));
	cmd->AddSequential(new DriveForward(5, 0.35));	//Reach the defence
	cmd->AddSequential(new DriveForward(6, 0.35));	//breach the defence

	return cmd;
}
