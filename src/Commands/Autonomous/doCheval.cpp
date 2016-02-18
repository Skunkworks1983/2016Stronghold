//doCheval.cpp

#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doCheval(startingPosition sp, goalPosition gp)
{
	AutoBase *cmd = new AutoBase("Autonomous-doCheval");
	//cmd->AddSequential(new ChevDeFris(CHEV_SPEED, CHEV_DIST, CHEV_SHORTDIST));
		//Add commands here
	return cmd;
}


