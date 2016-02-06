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
//this->collectorRotatorSetpoint = collectorRotatorSetpoint;
this->collectorRotatorPosition = collectorRotatorPosition;
this->kickerActivated = kickerActivated;
this->shootState = shootState;
this->rollerSpeed = rollerSpeed;
this->shootTime = shootTime;
sensorManager = SensorManager::getSensorManager();
collector = CommandBase::collector;
}

ShootLowGoal::~ShootLowGoal() {
	// TODO Auto-generated destructor stub
}

void ShootLowGoal::Initialize()
{
	shootTime = 0;
	shootState = SHOOT_STATE_AIMING;



}

void ShootLowGoal::Execute(){
	this->collectorRotatorPosition = sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	ExecuteAiming();
	ExecuteFiring();

	}

void ShootLowGoal::ExecuteAiming() {
	collector->setRotatorPosition(0);
	sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	collectorRotatorPosition = sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
			if (((collectorRotatorSetpoint - collectorRotatorPosition) < 5) && ((collectorRotatorSetpoint - collectorRotatorPosition) > -5)){
			shootState = SHOOT_STATE_FIRING;
			}

}
void ShootLowGoal::ExecuteFiring() {
	if (shootState == SHOOT_STATE_FIRING) {
		collector->activateShooter(true);
		if (fabs(collector->getRollerSpeed() - rollerSpeed) < SHOOTER_SPEED_TOLERANCE){
				collector->activateKicker(true);
				if (shootTime == 0){
					shootTime = clock();
				}
				if (clock() == shootTime + CLOCKS_PER_SEC){
					shootState = SHOOT_STATE_RESETTING;
				}
		}
	}
}
void ShootLowGoal::ExecuteResetting() {
	if (shootState == SHOOT_STATE_RESETTING) {
		collector->activateShooter(false);
		collector->activateKicker(false);
		shootState = SHOOT_STATE_FINISHED;
	}
}
bool ShootLowGoal::IsFinished()
{
 if (shootState == SHOOT_STATE_FINISHED){
 		return true;
 	 } else {
 			return false;
	}

}

void ShootLowGoal::End()
{
	collector->setRoller(Collector::KStop, 0);
}

void ShootLowGoal::Interrupted()
{
	collector->activateShooter(false);
	collector->activateKicker(false);
	End();
}
