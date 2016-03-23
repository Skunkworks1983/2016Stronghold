#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <RobotMap.h>
#include <TuningValues.h>

AutoBase *AutoBase::doRamP() {
	AutoBase *cmd = new AutoBase("Autonomous-doRamP");
	cmd->AddSequential(
			new DriveForwardStraight(REACH_DEFENCE_DISTANCE, REACH_DEFENCE_SPEED));
	cmd->AddSequential(new RotateShooter(cTOP));
	cmd->AddSequential(new DriveForwardStraight(0, RAMPART_SPEED));	//TODO: need solution because encoders are not accurate going over these types of defences

	return cmd;
}

