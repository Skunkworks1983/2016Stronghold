#ifndef RoughTerrainAuto_H
#define RoughTerrainAuto_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "Subsystems/SensorManager.h"
#include "DriveForward.h"
#include "TurnDegree.h"

class RoughTerrainAuto: public CommandGroup
{
private:
	float initialYaw;
	SensorManager * sensorManager;

public:
	RoughTerrainAuto();
};

#endif
