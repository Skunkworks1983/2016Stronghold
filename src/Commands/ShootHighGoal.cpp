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
#include <Commands/ShootHighGoal.h>

ShootHighGoal::ShootHighGoal() {
	// TODO Auto-generated constructor stub
this->collectorRotatorSetpoint = collectorRotatorSetpoint;
this->collectorRotatorPosition = collectorRotatorPosition;
this->shootState = shootState;
this->rollerSpeed = rollerSpeed;
this->shootTime = shootTime;
sensorManager = SensorManager::getSensorManager();
collector = CommandBase::collector;
}

ShootHighGoal::~ShootHighGoal() {
	// TODO Auto-generated destructor stub
}

void ShootHighGoal::Initialize()
{
	shootState = SHOOT_STATE_AIMING;
	shootTime = 0;

}

void ShootHighGoal::Execute()
{
	this->collectorRotatorPosition = sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	ExecuteAiming();
	ExecuteFiring();
	ExecuteResetting();
		}

void ShootHighGoal::ExecuteAiming() {
	if (shootState == SHOOT_STATE_AIMING) {
		collector->setRotatorPosition(collectorRotatorSetpoint);
		if ((fabs(collectorRotatorSetpoint - collectorRotatorPosition) < SHOOTER_AIM_TOLERANCE)){
				shootState = SHOOT_STATE_FIRING;
		}

	}
}
void ShootHighGoal::ExecuteFiring() {
	if (shootState == SHOOT_STATE_FIRING) {
		collector->activateShooter(true);
		if (fabs(collector->getRollerSpeed() - rollerSpeed) < SHOOTER_SPEED_TOLERANCE){
				collector->activateKicker(true);
				if (shootTime == 0) {
					shootTime = clock();
				}
				if (clock() == shootTime + CLOCKS_PER_SEC) {
					shootState = SHOOT_STATE_RESETTING;
				}
		}
	}
}
void ShootHighGoal::ExecuteResetting() {
	if (shootState == SHOOT_STATE_RESETTING) {
		collector->activateShooter(false);
		collector->activateKicker(false);
		collector->setRotatorPosition(0);
		shootState = SHOOT_STATE_FINISHED;
	}
}
bool ShootHighGoal::IsFinished()
{
	if (shootState == SHOOT_STATE_FINISHED) {
	return true;
 	 } else {
 			return false;
	}

}

void ShootHighGoal::End()
{

}

void ShootHighGoal::Interrupted()
{
	collector->activateShooter(false);
	collector->activateKicker(false);
	End();
}
