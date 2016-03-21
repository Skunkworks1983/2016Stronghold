//doCheval.cpp

#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/RotateShooter.h>

/**
 * Cheval De Fris Constants
 */
#define CHEV_SPEED 0.5
#define CHEV_SHORTDIST 3
#define CHEV_DIST 5

//TODO: rework this logic slightly
AutoBase *AutoBase::doCheval() {
	AutoBase*cmd = new AutoBase("Autonomous-doCheval");
	cmd->AddSequential(new DriveForward(5, 0.25));	//Reach the defence
	cmd->AddSequential(new RotateShooter(cCollect));
	cmd->AddSequential(new DriveForward(CHEV_SHORTDIST, CHEV_SPEED));
	cmd->AddSequential(new RotateShooter(cTOP));
	cmd->AddSequential(new DriveForward(CHEV_DIST, CHEV_SPEED));
	return cmd;
}

