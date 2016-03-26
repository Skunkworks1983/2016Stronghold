#include <Commands/Climbing/AutoRotateArm.h>
#include <Commands/Climbing/RotateArm.h>
#include <PIDController.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Climber.h>
#include <TuningValues.h>
#include <cstdio>

AutoRotateArm::AutoRotateArm(float target) : target(target)
{
	Requires(climber);
	curIt = 0;
	lastEnc = SensorManager::getSensorManager()->getSensor(SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet();
	curEnc = lastEnc;
	continueClimbing = false;
}

void AutoRotateArm::Initialize()
{
	climber->registerCommand(this);

	LOG_INFO("AutoRotateArm Initialize called with target %f", target);
	MotorManager::getMotorManager()->enablePID(PID_ID_ARM, target);
}

void AutoRotateArm::Execute()
{
	curEnc = SensorManager::getSensorManager()->getSensor(SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet();

	if(fabs(curEnc - lastEnc) < target*ARM_WIGGLE_TOLERANCE_PERCENT) {
		curIt++;
	} else {
		curIt = 0;
	}

	if(curIt >= CONTINUE_CLILMB_COUNTER) {
		continueClimbing = true;
		curIt = 0;
	}
	lastEnc = curEnc;
}

bool AutoRotateArm::IsFinished()
{
	return fabs(SensorManager::getSensorManager()->getSensor(
		   SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet()) > target - EPSILON		&&
			continueClimbing;
}

void AutoRotateArm::End()
{

}

void AutoRotateArm::Interrupted()
{

}
