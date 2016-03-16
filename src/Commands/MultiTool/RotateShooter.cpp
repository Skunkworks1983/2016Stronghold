#include <Commands/MultiTool/RotateShooter.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <SmartDashboard/SmartDashboard.h>
#include <cmath>
#include <cstdbool>
#include <cstdio>

#define COLLECTOR_MOVE_TOLERANCE 250

//TODO: Find the conversion ratio for encoder ticks to degrees
RotateShooter::RotateShooter(ShooterPosition pos) {
	Requires(shooter);
	SetInterruptible(true);
	test = 0;
	switch (pos) {
	case cTOP:
		target = COLLECTOR_ROTATION_ENCODER_TOP_TICKS;
		break;
	case cCollect:
		target = COLLECTOR_ROTATION_ENCODER_COLLECT_TICKS;
		break;
	case c45:
		target = COLLECTOR_ROTATION_ENCODER_45_TICKS;
		break;
	}
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
}

void RotateShooter::Initialize() {
	shooter->registerCommand(this);
	//motorManager->disablePID(PID_ID_COLLECTOR);
	motorManager->enablePID(PID_ID_COLLECTOR, target);
	char str[1024];
	sprintf(str, "CollectorMove Initialize target %f", target);
	Logger::getLogger()->log(str, Debug);
	SmartDashboard::PutNumber("target", target);
}

void RotateShooter::Execute() {
}

bool RotateShooter::IsFinished() {
	SmartDashboard::PutNumber("error",
			fabs(SensorManager::getSensorManager()->getSensor(
			SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet() - target));

	//bool notSameTarget = MotorManager::getMotorManager()->getPID(PID_ID_COLLECTOR)->GetSetpoint() != target;

	bool closeEnough = fabs(
			SensorManager::getSensorManager()->getSensor(
			SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet()
					- target) < COLLECTOR_MOVE_TOLERANCE;
	//return true;
	return closeEnough;
}

void RotateShooter::End() {
	SmartDashboard::PutBoolean("CollectorMoveRunning", false);
	//MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
	char str[1024];
	sprintf(str, "CollectorMove END Called for target %f", target);
	Logger::getLogger()->log(str, Debug);
	shooter->deregisterCommand(this);
}

void RotateShooter::Interrupted() {
	char str[1024];
	sprintf(str, "CollectorMove INTERRUPTED Called for target %f", target);
	Logger::getLogger()->log(str, Debug);
	End(); //MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
}