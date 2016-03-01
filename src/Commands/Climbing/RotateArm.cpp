#include <Commands/Climbing/RotateArm.h>
#include <PIDController.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Climber.h>
#include <TuningValues.h>
#include <cstdio>

RotateArm::RotateArm(float target) :
		target(target) {
	Requires(climber);
}

RotateArm::~RotateArm() {
}

void RotateArm::Initialize() {
	char str[1024];
	sprintf(str, "RotateArm Initialize called with target %f", target);
	writeToLogFile(LOGFILE_NAME, str);
	/*if (MotorManager::getMotorManager()->getPID(PID_ID_ARM)->IsEnabled()) {
		End();
		return;
	}*/
//	if (SensorManager::getSensorManager()->getSensor(SENSOR_CLIMBER_ARM_ENCODER)->PIDGet()
//			< 500) {
//		MotorManager::getMotorManager()->resetPID(PID_ID_ARM);
//	}
	MotorManager::getMotorManager()->enablePID(PID_ID_ARM, target);
	//climber->setSetpoint(target);
}

void RotateArm::Execute() {
	//get PID values
	//char str[1024];
	//sprintf(str, "ArmPower %f", MotorManager::getMotorManager()->get);
	//writeToLogFile(LOGFILE_NAME, str);
}

bool RotateArm::IsFinished() {
	/*if (target == getpid){
	 return true;
	 }
	 else {
	 return false;
	 } */
	return false;
}

void RotateArm::End() {
	char str[1024];
	sprintf(str, "RotateArm END called with target %f", target);
	writeToLogFile(LOGFILE_NAME, str);
	//MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
}

void RotateArm::Interrupted() {
	End();
}

