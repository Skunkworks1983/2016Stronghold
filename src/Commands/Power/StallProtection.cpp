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
	for(unsigned int i = 0; i < motorManager->motors.size(); i++) {
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
					switch(motor->parentSubsystem) {
						case DRIVEBASE:
							motorManager->disablePID(PID_ID_TURN_DEGREE);
							motorManager->disablePID(PID_ID_CAMERA);
							break;
						case WINCH:
							//No PIDs for that yet
							break;
						case ARM:
							//No PIDs for that yet
							break;
						case COLLECTOR_ROTATOR:
							//No PIDs for that yet
							break;
						case ROLLER:
							motorManager->disablePID(PID_ID_ROLLER);
							break;
						case SHOOTER:
							motorManager->disablePID(PID_ID_SHOOTER_1);
							motorManager->disablePID(PID_ID_SHOOTER_2);
							break;
						}
				}
			}
		} else {
			motor->overCurrentStartTime = 0;
		}

		if(motor->stoppedStartTime > MAX_STOP_TIME) {
			switch(motor->parentSubsystem) {
			case DRIVEBASE:
				motorManager->enablePID(PID_ID_TURN_DEGREE);
				motorManager->enablePID(PID_ID_CAMERA);
				break;
			case WINCH:
				//No PIDs for that yet
				break;
			case ARM:
				//No PIDs for that yet
				break;
			case COLLECTOR_ROTATOR:
				//No PIDs for that yet
				break;
			case ROLLER:
				motorManager->enablePID(PID_ID_ROLLER);
				break;
			case SHOOTER:
				motorManager->enablePID(PID_ID_SHOOTER_1);
				motorManager->enablePID(PID_ID_SHOOTER_2);
				break;
			}
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
