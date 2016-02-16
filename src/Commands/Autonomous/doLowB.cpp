#include <Commands\Autonomous\AutoBase.h>

AutoBase *AutoBase::doLowB(startingPosition sp, goalPosition gp)
{
	AutoBase *cmd = new AutoBase("Autonomous-doLowB");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	return cmd;
}




