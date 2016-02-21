#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doRamP()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doRamP");
	return cmd;
}




