//doCheval.cpp
#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Defences/ChevDeFris.h>
#include <TuningValues.h>

AutoBase *AutoBase::doCheval()
{
	AutoBase *cmd = new AutoBase((char*) "Autonomous-doCheval"); //Done on every auto, deprecated automatic conversion from string to char*
	cmd->AddSequential(new ChevDeFris(CHEV_SPEED, CHEV_DIST, CHEV_SHORTDIST));
	return cmd;

}

