#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doRamP()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRamP");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	return cmd;
}




