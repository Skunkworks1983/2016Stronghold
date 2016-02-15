#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doLowB()
{
	AutoBase *cmd = new AutoBase("Autonomous-doLowB");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	return cmd;
}




