/*
 * PortcullisAuto.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: s-2507264
 */

#include <Commands/PortcullisAuto.h>
#include <cmath>
#include <cstdbool>

Portcullis::Portcullis(float speed, float distance, float turnup){
	Requires(drivebase);
	Requires(collector);
	this->speed = speed;
	this->distance = distance;
	this->turnup = turnup;
	this->dt = 0;
	this->turn = turn;
	this->firststop = false;

}

void Portcullis::Initialize(){
	drivebase->resetEncoder();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	drivebase->getLeftDistance();


}
Portcullis::~Portcullis(){

}

void Portcullis::Execute(){
	this->dt = drivebase->getRightDistance();
	if (fabs(distance-dt) <= EPSILON && firststop==false) {
		this->firststop = true;
		drivebase->setRightSpeed(0);
		drivebase->setLeftSpeed(0);
	}
//	CollectorMove(turnup);
	if ((turnup - turn) < EPSILON){

	}
	this->dt = drivebase->getRightDistance();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	}


bool Portcullis::IsFinished(){
	if ((2*distance-dt) <= EPSILON && (turnup-turn) <= EPSILON){
		return true;
	}
	else {
		return false;
	}
}

void Portcullis::End(){
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
	CollectorMove(0);
}

void Portcullis::Interrupted(){
	End();
}
