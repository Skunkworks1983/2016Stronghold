#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>

AutoBase *AutoBase::doMoat() {
	AutoBase *cmd = new AutoBase("Autonomous-doMoat");
	cmd->AddSequential(new DriveForward(8, 1.0f));

	return cmd;
}
