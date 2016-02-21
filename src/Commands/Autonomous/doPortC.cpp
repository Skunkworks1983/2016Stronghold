#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doPortC()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doPortC");
	return cmd;
}




