#ifndef RoughTerrainAuto_H
#define RoughTerrainAuto_H

#include <Commands/CommandGroup.h>

class SensorManager;

class RoughTerrainAuto: public CommandGroup
{
private:
	float initialYaw;
	SensorManager * sensorManager;

public:
	RoughTerrainAuto();
};

#endif
