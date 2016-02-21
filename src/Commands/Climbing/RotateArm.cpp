#include <Commands/Climbing/RotateArm.h>
#include <Subsystems/Climber.h>
#include <TuningValues.h>
#include <Services/MotorManager.h>
#include <RobotMap.h>

RotateArm::RotateArm(float angleDegrees)
{
	this->angleDegrees = angleDegrees;
}

RotateArm::~RotateArm(){

}

void RotateArm::Initialize()
{
	MotorManager::getMotorManager()->setSpeed(CLIMBER_ARM_MOTOR_PORT, 1.0);
	MotorManager::getMotorManager()->enablePID(PID_ID_ARM, angleDegrees*CLIMBER_ARM_DEGREES_TO_ENCODER_TICKS);

}

void RotateArm::Execute()
{
//get PID values
}

bool RotateArm::IsFinished()
{
	/*if (angleDegrees == getpid){
		return true;
	}
	else {
		return false;
	} */
}

void RotateArm::End()
{
	MotorManager::getMotorManager()->disablePID(angleDegrees*CLIMBER_ARM_DEGREES_TO_ENCODER_TICKS);
	MotorManager::getMotorManager()->setSpeed(CLIMBER_ARM_MOTOR_PORT,0.0); //probably wrong
}

void RotateArm::Interrupted()
{
	End();
}

