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
#include <Commands/CollectBall.h>

CollectBall::CollectBall() {
	// TODO Auto-generated constructor stub
	this->collectorRotatorPosition = collectorRotatorPosition;
	this->rollerSpeed = rollerSpeed;
	this->collectTime = collectTime;
	this->collectState = collectState;
	sensorManager = SensorManager::getSensorManager();
	collector = CommandBase::collector;
}

CollectBall::~CollectBall() {
	// TODO Auto-generated destructor stub
}

void CollectBall::Initialize() {
	collectState = COLLECT_STATE_AIMING;
	collector->activateKicker(false);
	collector->activateShooter(false);
	collectTime = 0;

}

void CollectBall::Execute() {
	collectorRotatorPosition = sensorManager->GetEncoderPosition(
			COLLECTOR_ROTATOR_MOTOR_1_PORT);
	void ExecuteAiming();
	void ExecuteCollecting();
}
void CollectBall::ExecuteAiming() {
	if (collectState == COLLECT_STATE_AIMING) {
		collector->setRotatorPosition(0);
		sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
		if ((collectorRotatorPosition < 5) && (collectorRotatorPosition > -5)) {
			collectState = COLLECT_STATE_COLLECTING;
		}
	}
}

void CollectBall::ExecuteCollecting() {
	if (collectState == COLLECT_STATE_COLLECTING) {
		collector->activateCollector(true);
		if (collectTime == 0) {
			collectTime = clock();
		}
		if (clock() == collectTime + CLOCKS_PER_SEC) {
			collectState = COLLECT_STATE_RESETTING;
		}
	}
}

void CollectBall::ExecuteResetting() {
	if (collectState == COLLECT_STATE_RESETTING) {
		collector->activateCollector(false);
		collectState = COLLECT_STATE_FINISHED;
	}
}

bool CollectBall::IsFinished() {
	if (collectState == COLLECT_STATE_FINISHED) {
		return true;
	} else {
		return false;
	}
}

void CollectBall::End() {

}

void CollectBall::Interrupted() {
	collectState = COLLECT_STATE_RESETTING;
	End();
}
