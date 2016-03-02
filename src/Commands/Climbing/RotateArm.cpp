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

void RotateArm::Initialize() {
	climber->registerCommand(this);

	char str[1024];
	sprintf(str, "RotateArm Initialize called with target %f", target);
	writeToLogFile(LOGFILE_NAME, str);

	//MotorManager::getMotorManager()->resetPID(PID_ID_ARM);

	MotorManager::getMotorManager()->enablePID(PID_ID_ARM, target);
}

void RotateArm::Execute() {

}

bool RotateArm::IsFinished() {
	return fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet()) > target;
}

void RotateArm::End() {
	climber->deregisterCommand(this);
	char str[1024];
	sprintf(str, "RotateArm END called with target %f", target);
	writeToLogFile(LOGFILE_NAME, str);
}

void RotateArm::Interrupted() {
	End();
}

