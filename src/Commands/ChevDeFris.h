#ifndef ChevDeFris_H
#define ChevDeFris_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <Subsystems/drivebase.h>
#include <Subsystems/Collector.h>
#define EPSILON .0005f

class ChevDeFris: public CommandBase
{
private:
	float speed; // how fast to go during this breach
	float distance; // how far to go in order to breach the cheval de fris
	float turn; // how far to turn the collector to lower the teeter-totter
	float turning; // how far the collector has turned
	float dt;  // distance traveled since command started
	bool firststop; // have we driven to the Cheval yet?
public:
	ChevDeFris(float speed, float distance, float turndown);
	~ChevDeFris();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();


};

#endif
