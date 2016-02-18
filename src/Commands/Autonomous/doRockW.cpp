#include "AutoBase.h"
#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doRockW()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRockW");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	return cmd;
}




