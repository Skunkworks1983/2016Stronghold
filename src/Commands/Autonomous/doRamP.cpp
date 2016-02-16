#include <Commands\Autonomous\AutoBase.h>

AutoBase *AutoBase::doRamP(startingPosition sp, goalPosition gp)
{
	AutoBase *cmd = new AutoBase("Autonomous-doRamP");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	return cmd;
}




