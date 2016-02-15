#include "RoughTerrainAuto.h"

RoughTerrainAuto::RoughTerrainAuto()
{
	sensorManager = SensorManager::getSensorManager();
	float initialYaw = sensorManager->getYaw();
	AddSequential(new DriveForward(5, 1));
	AddSequential(new TurnDegree(sensorManager->getYaw() - initialYaw));

}
