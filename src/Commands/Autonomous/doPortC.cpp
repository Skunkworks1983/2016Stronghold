#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunCollector.h>
#include <Subsystems/Shooter.h>

#define PORT_DISTANCE 15
#define PORT_SPEED .25

AutoBase *AutoBase::doPortC()
{
	AutoBase *cmd = new AutoBase("Autonomous-doPortC");
#if USE_SHOOTER
	cmd->AddSequential(new RotateShooter(cCollect));
#endif
	cmd->AddParallel(new DriveForward(PORT_DISTANCE, PORT_SPEED));
	cmd->AddSequential(new RunCollector(Shooter::KForward, 1.0, 3));

	return cmd;
}


/*lower shooter,
 * move forward
 * raise shooter
 * move forward/drive through
*/
