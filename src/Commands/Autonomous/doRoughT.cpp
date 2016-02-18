#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doRoughT(startingPosition sp, goalPosition gp)
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	return cmd;
}




