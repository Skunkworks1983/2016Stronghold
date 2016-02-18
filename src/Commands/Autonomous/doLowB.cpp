#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <RobotMap.h>
#include <Commands/LowBarAuto.h>

AutoBase *AutoBase::doLowB()
{
	AutoBase *cmd = new AutoBase("Autonomous-doLowB");
	cmd->AddSequential(new DriveForward(LOWBAR_ENCODER_TICKS, LOWBAR_SPEED));
	cmd->AddSequential(new LowBarAuto(LOWB_DISTANCE, LOWB_SPEED,LOWB_TURN));
		//Add commands here
	return cmd;
}




