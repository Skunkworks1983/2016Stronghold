#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doPortC(startingPosition sp, goalPosition gp)
{
	AutoBase *cmd = new AutoBase("Autonomous-doPortC");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	return cmd;
}




