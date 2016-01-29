/*
 * TurnDegree.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: S-4032218
 */
#include "TurnDegree.h"


TurnDegree::TurnDegree(double degree, double placeholder)
{
	this->degree = degree;
}

TurnDegree::~TurnDegree()
{

}

void TurnDegree::Initialize()
{
	drivebase->resetEncoder();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(-speed);
}

void TurnDegree::Execute()
{

}

bool TurnDegree::IsFinished()
{
	if (drivebase->getLeftDistance() >= (degree * ENCODER_TURN_RADIUS_RATIO)) {
		return true;

	}
	else{
			return false;
		}
}






void TurnDegree::End()
{
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
}

void TurnDegree::Interrupted()
{
	End();
}
