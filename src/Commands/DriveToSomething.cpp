/*
 *  DriveToSomething.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: s-2507264
 */
#include<Subsystems/Drivebase.h>
#include<Commands/DriveToSomething.h>
#define EPSILON 0.0005f // EPSILON checks to see if it reaches the distance.

DriveToSomething::DriveToSomething(float distance, float speed){
	Requires(drivebase);
	this->distance = distance;
	this->speed = speed;
	this->dt = dt;

}

DriveToSomething::~DriveToSomething(){

}

void DriveToSomething::Initialize(){
	drivebase->resetEncoder();
	drivebase->setRightSpeed(speed);
	drivebase->setLeftSpeed(speed);


}

void DriveToSomething::Execute(){
	this->dt = drivebase->getRightDistance();

	if (distance-dt < EPSILON) {
		float newSpeed = (speed*.2)*((distance - dt)/distance);
		drivebase->setLeftSpeed(newSpeed);
		drivebase->setRightSpeed(newSpeed);
	}

	if (IsFinished()) {
		End();
	}
}

bool DriveToSomething::IsFinished(){

	if ((distance-dt) <= EPSILON) {
		return true;
	}
	else {
		return false;
	}

}

void DriveToSomething::End(){
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);

}

void DriveToSomething::Interrupted(){
	End();

}
