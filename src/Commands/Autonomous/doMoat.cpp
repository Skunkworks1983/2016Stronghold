#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doMoat()
{
	AutoBase *cmd = new AutoBase("Autonomous-doMoat");
	//cmd->AddSequential(new DriveForward(myCommandParameters));
		//Add commands here
	return cmd;
}
