#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/Driving/TurnRightEncoder.h>
#include <Commands/MultiTool/ActivateRollers.h>
#include <Commands/MultiTool/CollectorMove.h>
#include <Subsystems/Collector.h>
#include <iostream>

AutoBase *AutoBase::doLowBarandScore()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doLowB");
	std::cout << "Reached doLowB after AutoBase cmd pointer creation" << std::endl;
	cmd->AddSequential(new CollectorMove(cLowBar));
	cmd->AddSequential(new DriveForward(5, 0.25));	//Reach the defence
	cmd->AddSequential(new DriveForward(11.7, 0.25));	//breach the defence
	cmd->AddSequential(new TurnRightEncoder(58));
	cmd->AddSequential(new DriveForward(7.5, .25));
	cmd->AddSequential(new ActivateRollers(Collector::rollerDirection::KBackward, 1000));

	return cmd;
}
