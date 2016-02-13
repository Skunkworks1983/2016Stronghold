#include <Commands\Autonomous\AutoBase.h>

AutoBase *AutoBase::doRockW(startingPosition sp, goalPosition gp)
{
	AutoBase *cmd = new AutoBase("Autonomous-doRockW");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	return cmd;
}




