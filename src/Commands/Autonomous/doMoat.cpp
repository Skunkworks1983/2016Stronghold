#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doMoat()
{
	sensorManager = SensorManager::getSensorManager();

	AutoBase *cmd = new AutoBase("Autonomous-doMoat");
	//cmd->AddSequential(new DriveForward(myCommandParameters));
		//Add commands here
	initialPosition = sensorManager->getYaw();
	AddSequential(new DriveForward(5, 1));
	AddSequential(new TurnDegree(sensorManager->getYaw() - initialPosition));
	return cmd;
}
