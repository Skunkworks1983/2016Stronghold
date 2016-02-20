#include "AutoBase.h"
#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doRockW()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRockW");
	cmd->AddSequential(new DriveForward(8, 1.0));
	return cmd;
}




