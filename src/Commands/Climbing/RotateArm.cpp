#include <Commands/Climbing/RotateArm.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <TuningValues.h>
#include <cstdio>

RotateArm::RotateArm(float target) {
	this->target = target;
}

RotateArm::~RotateArm() {

}

void RotateArm::Initialize() {
	//MotorManager::getMotorManager()->setSpeed(CLIMBER_ARM_MOTOR_PORT, 1.0);
	char str[1024];
	sprintf(str, "RotateArm Initialize called with target %f", target);
	writeToLogFile(LOGFILE_NAME, str);
	MotorManager::getMotorManager()->enablePID(PID_ID_ARM, target);
}

void RotateArm::Execute() {
	//get PID values
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
	//MotorManager::getMotorManager()->disablePID(target*CLIMBER_ARM_DEGREES_TO_ENCODER_TICKS);
	//MotorManager::getMotorManager()->setSpeed(CLIMBER_ARM_MOTOR_PORT,0.0); //probably wrong
		MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
}

void RotateArm::Interrupted() {
	End();
}

