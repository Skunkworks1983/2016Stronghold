/*
 * .cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: s-4032218
 */
/*
 * Problems with this program:
 * Need the actual numbers for the rotator position (numbers for collectorRotatorSetpoint

 */
#include <Commands/ShootLowGoal.h>

ShootLowGoal::ShootLowGoal() {
	// TODO Auto-generated constructor stub
this->speed = speed;
this->collectorRotatorSetpoint = collectorRotatorSetpoint;
this->collectorRotatorPosition = collectorRotatorPosition;
this->kickerActivated = kickerActivated;
}

ShootLowGoal::~ShootLowGoal() {
	// TODO Auto-generated destructor stub
}

void ShootLowGoal::Initialize()
{
	shootState = SHOOT_STATE_AIMING;


}

void ShootLowGoal::Execute(){
	switch (shootState){
		case SHOOT_STATE_AIMING:
			ExecuteAiming();
		break;
		case SHOOT_STATE_FIRING:
			ExecuteFiring();
		break;
	}



}

void ShootLowGoal::ExecuteAiming() {
	speed = 1;
	SensorManager * sensorManager = SensorManager::getSensorManager();
	Collector * collector = CommandBase::collector;
	collector->setRotatorPosition(collectorRotatorSetpoint);
	sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	collectorRotatorPosition = sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
			if (((collectorRotatorSetpoint - collectorRotatorPosition) < 5) && ((collectorRotatorSetpoint - collectorRotatorPosition) > -5)){
			shootState = SHOOT_STATE_FIRING;
			}

}
void ShootLowGoal::ExecuteFiring() {
	MotorManager * MotorManager = MotorManager::getMotorManager();
	Collector * collector = CommandBase::collector;
			collector->setRoller(Collector::KBackward, speed);
			if ((MotorManager->getSpeed(COLLECTOR_ROLLER_MOTOR_1_PORT) == speed) && (COLLECTOR_ROLLER_MOTOR_2_PORT == speed)){
				MotorManager->setSpeed(COLLECTOR_KICKER_MOTOR_PORT, 1);
					kickerActivated = true;
			}
		}

bool ShootLowGoal::IsFinished()
{
 if (kickerActivated = true){
 		return true;
 	 } else {
 			return false;
	}

}

void ShootLowGoal::End()
{
	Collector * collector = CommandBase::collector;
	collector->setRoller(Collector::KStop, 0);
}

void ShootLowGoal::Interrupted()
{
	End();
}
