#include <Commands/Driving/DriveForward.h>
#include <Commands/Driving/TurnDegree.h>
#include <Commands/RoughTerrainAuto.h>
#include <Services/SensorManager.h>

RoughTerrainAuto::RoughTerrainAuto()
{
	sensorManager = SensorManager::getSensorManager();
	float initialYaw = sensorManager->getYaw();
	AddSequential(new DriveForward(5, 1));
	AddSequential(new TurnDegree(sensorManager->getYaw() - initialYaw));

}
