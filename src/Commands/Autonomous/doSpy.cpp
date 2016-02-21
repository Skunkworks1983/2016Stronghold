#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doSpy()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doSpy");
	return cmd;
}



