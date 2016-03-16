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
	char str[1024];
	sprintf(str, "RotateArm Initialize called with target %f", target);
	Logger::getLogger()->log(str, Info);
	climber->registerCommand(this);

	MotorManager::getMotorManager()->enablePID(PID_ID_ARM, target);
}

void RotateArm::Execute() {
	//get PID values
	//char str[1024];
	//sprintf(str, "ArmPower %f", MotorManager::getMotorManager()->get);
	//Logger::getLogger()->log(str, Info);

}

bool RotateArm::IsFinished() {

	return fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet()) > target - 250;
}

void RotateArm::End() {
	char str[1024];
	sprintf(str, "RotateArm END called with target %f", target);
	Logger::getLogger()->log(str, Info);
	climber->deregisterCommand(this);

	//MotorManager::getMotorManager()->disablePID(target*CLIMBER_ARM_DEGREES_TO_ENCODER_TICKS);
	//MotorManager::getMotorManager()->setSpeed(CLIMBER_ARM_MOTOR_PORT,0.0); //probably wrong
	//MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
}

void RotateArm::Interrupted() {
	End();
}

