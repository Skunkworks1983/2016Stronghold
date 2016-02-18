#include "Climb.h"
#include <Subsystems/Climber.h>

Climb::Climb(float winchspeed){
	Requires(CommandBase::climber);
	this->winchspeed = winchspeed;
	this->winchStartPos = 0;


}

Climb::~Climb(){

}

void Climb::Initialize()
{
	climber->setWinchSpeed(winchspeed);
	this->winchStartPos = climber->getWinchPos();
	this->winchspeed = winchspeed;

}


void Climb::Execute()
{
	climber->getWinchSpeed();
	float currentWinchPos = climber->getWinchPos();
	float totaldistance = currentWinchPos - winchStartPos;

	if(totaldistance > CLIMBDISTANCE)
		climber->setWinchSpeed(0);
	}


bool Climb::IsFinished()
{
	float currentWinchPos = climber->getWinchPos();
	float totaldistance = currentWinchPos - winchStartPos;
	if(totaldistance > CLIMBDISTANCE){
		return true;
	}
	return false;
}


void Climb::End()
{
	climber->setWinchSpeed(0);
}

void Climb::Interrupted()
{
	End();
}
