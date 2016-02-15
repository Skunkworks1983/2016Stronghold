#include <Commands/Autonomous/AutoBase.h>
#include <Commands/DriveForward.h>
#include <RobotMap.h>

AutoBase *AutoBase::doLowB(startingPosition sp, goalPosition gp)
{
	switch (sp){
	case spy:
		break;
	case lowBar:
		break;
	case posZero:
		break;
	case posOne:
		break;
	case posTwo:
		break;
	case posThree:
		break;
	}
	AutoBase *cmd = new AutoBase("Autonomous-doLowB");
	cmd->AddSequential(new DriveForward(LOWBAR_ENCODER_TICKS, LOWBAR_SPEED));
	return cmd;
}




