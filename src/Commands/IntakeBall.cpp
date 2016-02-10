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
#include <Commands/IntakeBall.h>

IntakeBall::IntakeBall() {
	// TODO Auto-generated constructor stub
	this->collectorRotatorPosition = collectorRotatorPosition;
	this->rollerSpeed = rollerSpeed;
	this->collectTime = collectTime;
	this->intakeState = intakeState;
	sensorManager = SensorManager::getSensorManager();
	collector = CommandBase::collector;
}

IntakeBall::~IntakeBall() {
	// TODO Auto-generated destructor stub
}

void IntakeBall::Initialize() {
	intakeState = INTAKE_STATE_COLLECTING;
	collector->activateKicker(false);
	collector->activateShooter(false);
	collectTime = 0;

}

void IntakeBall::Execute() {
	collectorRotatorPosition = sensorManager->GetEncoderPosition(
			COLLECTOR_ROTATOR_MOTOR_1_PORT);
	void ExecuteAiming();
	void ExecuteCollecting();
}

void IntakeBall::ExecuteCollecting() {
	if (intakeState == INTAKE_STATE_COLLECTING) {
		collector->activateCollector(true);
		if (collectTime == 0) {
			collectTime = clock();
		}
		if (clock() == collectTime + CLOCKS_PER_SEC) {
			intakeState = INTAKE_STATE_RESETTING;
		}
	}
}

void IntakeBall::ExecuteResetting() {
	if (intakeState == INTAKE_STATE_RESETTING) {
		collector->activateCollector(false);
		intakeState = INTAKE_STATE_FINISHED;
	}
}

bool IntakeBall::IsFinished() {
	if (intakeState == INTAKE_STATE_FINISHED) {
		return true;
	} else {
		return false;
	}
}

void IntakeBall::End() {

}

void IntakeBall::Interrupted() {
	intakeState = INTAKE_STATE_RESETTING;
	End();
}
