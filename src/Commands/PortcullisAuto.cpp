/*
 * PortcullisAuto.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: s-2507264
 */

#include <Commands/PortcullisAuto.h>
#include <cmath>
#include <cstdbool>

PortcullisAuto::PortcullisAuto(float speed, float distance, float turn){
	Requires(drivebase);
	Requires(collector);
	this->speed = speed;
	this->distance = distance;
	this->turn = turn;
	this->dt = 0;
	this->turning = 0;
	this->firststop = false;
}

void PortcullisAuto::Initialize(){
	drivebase->resetEncoder();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	drivebase->getLeftDistance();


}
PortcullisAuto::~PortcullisAuto(){

}

void PortcullisAuto::Execute(){
	this->dt = drivebase->getRightDistance();
	if (fabs(distance-dt) <= EPSILON && firststop==false) {
		this->firststop = true;
		drivebase->setRightSpeed(0);
		drivebase->setLeftSpeed(0);
	}
	collector->setRotatorPosition(turn);
	if ((turn - turning) < EPSILON){

	}
	this->dt = drivebase->getRightDistance();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	}


bool PortcullisAuto::IsFinished(){
	if ((2*distance-dt) <= EPSILON && (turn-turning) <= EPSILON){
		return true;
	}
	else {
		return false;
	}
}

void PortcullisAuto::End(){
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
	collector->setRotatorPosition(0);
}

void PortcullisAuto::Interrupted(){
	End();
}
