#include "ChevDeFris.h"
#define REACHDT 3.0f

ChevDeFris::ChevDeFris(float speed, float distance, float turn){
	Requires(drivebase);
	Requires(collector);
	this->speed = speed;
	this->distance = distance;
	this->turn = turn;
	this->dt = 0;
	this->turning = 0;
	this->firststop = false;

}

void ChevDeFris::Initialize(){
	drivebase->resetEncoder();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	collector->setRotatorPosition(turn);


}
ChevDeFris::~ChevDeFris(){

}

void ChevDeFris::Execute(){
	this->dt = drivebase->getRightDistance();
	if (fabs(distance-dt) <= EPSILON && firststop==false) {
		this->firststop = true;
		drivebase->setRightSpeed(0);
		drivebase->setLeftSpeed(0);
	}
	collector->setRotatorPosition(turning); //getmotor not set
	if ((turn - turning) < EPSILON){
//down for 1 in then go up
	}
	if (dt >= REACHDT){
		collector->setRotatorPosition(turn); //turninging back to the original position
	}
	//define the dt value which is not dt
	this->dt = drivebase->getRightDistance();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	}


bool ChevDeFris::IsFinished(){
	if ((2*distance-dt) <= EPSILON && (turn-turning) <= EPSILON){
		return true;
	}
	else {
		return false;
	}
}

void ChevDeFris::End(){
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
	collector->setRotatorPosition(0);
}

void ChevDeFris::Interrupted(){
	End();
}
