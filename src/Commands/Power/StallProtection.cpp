#include "StallProtection.h"

StallProtection::StallProtection()
{
	motorManager = MotorManager::getMotorManager();
}

void StallProtection::Initialize()
{

}

void StallProtection::Execute()
{
	for(int i = 0; i < motorManager->motors.size(); i++) {
		Motor * motor = motorManager->motors[i];
		if(motor->talon->GetOutputCurrent() >= motor->maxCurrent) {
			if(motor->overCurrentStartTime == 0) {
				motor->overCurrentStartTime = GetFPGATime();
			} else {
				/*If the motor has been over current for too long (time set divided by the amount its over by),
				  then stop the motor so it doesn't break*/
				if(GetFPGATime() - motor->overCurrentStartTime >
				   OVER_MAX_TIME/(motor->talon->GetOutputCurrent() / motor->maxCurrent)) {
					motor->overCurrentStartTime = 0;
					motor->talon->Set(0);
					motor->stoppedStartTime = GetFPGATime();
				}
			}
		}

		if(motor->stoppedStartTime > MAX_STOP_TIME) {
			motor->stoppedStartTime = 0;
			motorManager->setSpeed(i, motor->speed);
		}
	}
}

bool StallProtection::IsFinished()
{
	return false;
}

void StallProtection::End()
{

}

void StallProtection::Interrupted()
{

}
