#include <Commands\Autonomous\AutoBase.h>

AutoBase *AutoBase::doSpy(startingPosition sp, goalPosition gp)
{
	AutoBase *cmd = new AutoBase("Autonomous-doSpy");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	return cmd;
}



