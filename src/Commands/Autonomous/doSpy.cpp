#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doSpy()
{
	AutoBase *cmd = new AutoBase("Autonomous-doSpy");
	//cmd->AddSequential(new myCommand(myCommandParameters));
	return cmd;
}



