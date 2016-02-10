#include "Climb.h"
#include <Subsystems/Climber.h>

Climb::Climb(float winchspeed){
	Requires(climber);
	this->winchspeed = winchspeed;
	this->winchStartPos = 0;


}

Climb::~Climb(){

}

void Climb::Initialize()
{
	climber->setwinchSpeed(winchspeed);
	this->winchStartPos = climber->getWinchEncoder();
	this->winchspeed = winchspeed;

}


void Climb::Execute()
{
	climber->getwinchSpeed();
	float currentWinchPos = climber->getWinchEncoder();
	float totaldistance = currentWinchPos - winchStartPos;

	if(totaldistance > CLIMBDISTANCE)
		climber->setwinchSpeed(0);
	}


bool Climb::IsFinished()
{
	float currentWinchPos = climber->getWinchEncoder();
	float totaldistance = currentWinchPos - winchStartPos;
	if(totaldistance > CLIMBDISTANCE){
		return true;
	}
	return false;
}


void Climb::End()
{
	climber->setwinchSpeed(0);
}

void Climb::Interrupted()
{
	End();
}
