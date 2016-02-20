#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");
	//cmd->AddSequential(new myCommand(myCommandParameters));
		//Add commands here
	sensorManager = SensorManager::getSensorManager();
	initialPosition = sensorManager->getYaw();
	AddSequential(new DriveForward(5, 1));
	AddSequential(new TurnDegree(sensorManager->getYaw() - initialPosition));
	return cmd;
	return cmd;
}




