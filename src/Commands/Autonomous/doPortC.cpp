#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <TuningValues.h>

#define PORT_DISTANCE 0
#define PORT_SPEED 0
AutoBase *AutoBase::doPortC()
{
	AutoBase *cmd = new AutoBase("Autonomous-doPortC");
	cmd->AddSequential(new RotateShooter(cCollect));
	cmd->AddSequential(new DriveForward(REACH_DEFENCE_DISTANCE, REACH_DEFENCE_SPEED));
	cmd->AddSequential(new DriveForward(PORT_DISTANCE, PORT_SPEED));
	cmd->AddParallel(new RotateShooter(cTOP));

	return cmd;
}


/*lower shooter,
 * move forward
 * raise shooter
 * move forward/drive through
*/
