#ifndef ChevDeFris_H
#define ChevDeFris_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <Subsystems/Drivebase.h>
#include <Subsystems/Collector.h>
#define EPSILON .0005f
#include <Subsystems/SensorManager.h>
#include <RobotMap.h>

class ChevDeFris: public CommandBase
{
private:
	float speed; // how fast to go during this breach
	float distance; // how far to go in order to breach the cheval de fris
	double turning; // how far the collector has turned
	float dt;  // distance traveled since command started
	bool firststop; // have we driven to the Cheval yet?
	float shortdis;// 2nd stop for a short distant
public:
	ChevDeFris(float speed, float distance, float shortdis);
	~ChevDeFris();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();


};

#endif
