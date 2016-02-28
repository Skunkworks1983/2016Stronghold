#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/CollectorMove.h>
#include <TuningValues.h>

#define RAMPART_SPEED 0

AutoBase *AutoBase::doRamP() {
	AutoBase *cmd = new AutoBase("Autonomous-doRamP");
	cmd->AddSequential(
			new DriveForward(REACH_DEFENCE_DISTANCE, REACH_DEFENCE_SPEED));
	cmd->AddSequential(new CollectorMove(cTOP));
	cmd->AddSequential(new DriveForward(0, RAMPART_SPEED));	//TODO: need solution because encoders are not accurate going over these types of defences

	return cmd;
}

