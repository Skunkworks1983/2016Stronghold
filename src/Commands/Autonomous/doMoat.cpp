#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>

AutoBase *AutoBase::doMoat() {
	AutoBase *cmd = new AutoBase("Autonomous-doMoat");
	cmd->AddParallel(new RotateShooter(cTOP));
	cmd->AddSequential(new RunNewCollector(.3));
	cmd->AddSequential(new DriveForward(5, 1.0f));	//Reach the defence
	cmd->AddSequential(new DriveForward(4.5, 1.0f));	//breach the defence
	return cmd;
}
