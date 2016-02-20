#ifndef Climb_H
#define Climb_H

#include <CommandBase.h>
#include <cstdbool>
#include <Subsystems/Climber.h>
#define CLIMBDISTANCE 50.f

class Climb: public CommandBase
{
private:
	float winchspeed;
	float winchStartPos;
public:
	Climb(float winchspeed);
	~Climb();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
