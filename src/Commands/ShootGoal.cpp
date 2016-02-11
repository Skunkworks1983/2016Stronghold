/*
 * .cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: s-4032218
 */
/*
 * Problems with this program:
 * Need the actual numbers for the rotator position (numbers for collectorRotatorSetpoint
 * THIS FILE IS OBSOLETE, AND BEING REPLACED WITH HIGHGOALCOMMANDGROUP AND LOWGOALCOMMANDGROUP
#include <Commands/ShootGoal.h>

ShootGoal::ShootGoal() {
	// TODO Auto-generated constructor stub

sensorManager = SensorManager::getSensorManager();
collector = CommandBase::collector;
this->shootState = shootState;
this->shootTime = shootTime;
this->rollerSpeed = rollerSpeed;
}

ShootGoal::~ShootGoal() {
	// TODO Auto-generated destructor stub
}

void ShootGoal::Initialize()
{
	shootState = SHOOT_STATE_FIRING;
	shootTime = 0;

}

void ShootGoal::Execute()
{
	this->collectorRotatorPosition = sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	ExecuteFiring();
	ExecuteResetting();
		}


void ShootGoal::ExecuteFiring() {
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
void ShootGoal::ExecuteResetting() {
	if (shootState == SHOOT_STATE_RESETTING) {
		collector->activateShooter(false);
		collector->activateKicker(false);
		shootState = SHOOT_STATE_FINISHED;
	}
}
bool ShootGoal::IsFinished()
{
	if (shootState == SHOOT_STATE_FINISHED) {
	return true;
 	 } else {
 			return false;
	}

}

void ShootGoal::End()
{

}

void ShootGoal::Interrupted()
{
	collector->activateShooter(false);
	collector->activateKicker(false);
	End();
}

 */
