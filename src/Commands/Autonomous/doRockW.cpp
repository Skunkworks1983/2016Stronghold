#include "AutoBase.h"
#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doRockW()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doRockW");
	return cmd;
}




