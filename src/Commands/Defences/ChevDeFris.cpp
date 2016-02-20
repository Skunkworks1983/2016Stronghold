#include <Commands/Defences/ChevDeFris.h>
#include <Subsystems/Collector.h>
#include <Subsystems/Drivebase.h>
#include <cmath>

ChevDeFris::ChevDeFris(float speed, float distance, float shortdis){
	Requires(drivebase);
	Requires(collector);
	this->speed = speed;
	this->distance = distance;
	this->dt = 0; // distance travel starts at 0, using encoder
	this->turning = 0; //start turning from 0, encoder
	this->firststop = false;
	this->shortdis = shortdis; //going for a short distance after firststop
}
void ChevDeFris::Initialize(){
	drivebase->resetEncoder();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	collector->setRotatorPosition(1.0f);
}
ChevDeFris::~ChevDeFris(){
}
void ChevDeFris::Execute(){
	this->dt = drivebase->getRightDistance();
	if (fabs(distance-dt) <= EPSILON && firststop==false) {
		this->firststop = true;
		drivebase->setRightSpeed(0);
		drivebase->setLeftSpeed(0);
		collector->setRotatorPosition(0);
	}
	SensorManager * sensorManager = SensorManager::getSensorManager();
	this->turning = sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	if ((sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT) - COLLECTOR_TURNDOWN) < EPSILON && (shortdis + distance) - dt > EPSILON)	{
		drivebase->setRightSpeed(speed);
		drivebase->setLeftSpeed(speed);
	}
			if (((shortdis+distance) - dt) < EPSILON ){
				drivebase->setRightSpeed(0);
				drivebase->setLeftSpeed(0);
				collector->setRotatorPosition(COLLECTOR_TURNUP);
			}
				if ((sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT) - COLLECTOR_TURNUP) < EPSILON ){
						this->dt = drivebase->getRightDistance();
							drivebase->setLeftSpeed(speed);
							drivebase->setRightSpeed(speed);
	}

}
bool ChevDeFris::IsFinished(){
	if (((2*distance + shortdis)-dt) <= EPSILON && (COLLECTOR_TURNUP-turning) <= EPSILON){
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
