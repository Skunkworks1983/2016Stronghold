#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/Driving/RotateTowardCameraTarget.h>
#include <Commands/Driving/TurnRightEncoder.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunCollector.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/PIDShot.h>
#include <Commands/TimeOut.h>
#include <Subsystems/Shooter.h>

AutoBase *AutoBase::doLowBarandScore() {
	AutoBase *cmd = new AutoBase((char*) "Autonomous-doLowB");
	cmd->AddSequential(new RunNewCollector(.3));
	cmd->AddParallel(new RotateShooter(cCollect));
	cmd->AddSequential(new DriveForward(-5, -0.4));	//Reach the defence
	cmd->AddSequential(new DriveForward(-11.02, -0.4));	//breach the defence
	cmd->AddParallel(new RotateShooter(cTOP));
#if PRACTICE_BOT
	cmd->AddSequential(new TurnRightEncoder(70));
#else
	cmd->AddSequential(new TurnRightEncoder(60));
#endif

	const double shooter_batter_speed = 55.35;
	cmd->AddSequential(new RunCollector(Shooter::KBackward, 1.0, .1));
	cmd->AddSequential(new RunCollector(Shooter::KForward, 1.0, .15));
	cmd->AddSequential(new RunCollector(Shooter::KBackward, 1.0, .3));
	cmd->AddSequential(new RunCollector(Shooter::KBackward, 1.0, .1));
	cmd->AddSequential(new RunCollector(Shooter::KForward, 1.0, .15));
	cmd->AddSequential(new RunCollector(Shooter::KBackward, 1.0, .3));
	cmd->AddParallel(
			new PIDShot(shooter_batter_speed + 1, shooter_batter_speed - 1));

	cmd->AddSequential(new DriveForward(-3, -0.2));
	cmd->AddParallel(new RotateTowardCameraTarget(-.2, -1600));
	cmd->AddSequential(new AutoRunCollector());
	cmd->AddSequential(new TimeOut(15));
	return cmd;
}
