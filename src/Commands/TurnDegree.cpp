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
	this->placeholder = placeholder;
}

TurnDegree::~TurnDegree()
{

}

void TurnDegree::Initialize()
{
	TurnDegree::SetSetPoint(40000);
	drivebase->resetEncoder();
	TurnDegree::SetLeftSpeed(speed);
	TurnDegree::SetRightSpeed(-speed);
}

void TurnDegree::Execute()
{

}

bool TurnDegree::IsFinished()
{
	if (drivebase->getLeftDistance() >= (degree * placeholder)) {
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
