#include <Commands/Autonomous/AutoBase.h>
#include <Commands/LowBarAuto.h>
AutoBase *AutoBase::doLowB()
{
	AutoBase *cmd = new AutoBase("Autonomous-doLowB");
	cmd->AddSequential(new LowBarAuto(LOWB_DISTANCE, LOWB_SPEED,LOWB_TURN));
		//Add commands here
	return cmd;
}




