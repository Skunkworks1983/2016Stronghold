#include <Commands/MultiTool/CollectorMove.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>
#include <cstdio>
#define COLLECTOR_MOVE_TOLERANCE 100

//TODO: Find the conversion ratio for encoder ticks to degrees
CollectorMove::CollectorMove(CollectorPosition pos) {
	Requires(collector);
	switch (pos) {
	case cTOP:
		target = COLLECTOR_ROTATION_ENCODER_TOP_TICKS;
		break;
	case cLowBar:
		target = COLLECTOR_ROTATION_ENCODER_LOWB_TICKS;
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

void CollectorMove::Initialize() {
	//Scheduler::GetInstance()->Remove(collector->GetCurrentCommand());

	motorManager->disablePID(PID_ID_COLLECTOR);
	motorManager->enablePID(PID_ID_COLLECTOR, target);
	char str[1024];
	sprintf(str, "CollectorMove Initialize target %f", target);
	writeToLogFile(LOGFILE_NAME, str);
	SmartDashboard::PutNumber("target", target);
}

void CollectorMove::Execute() {
}

bool CollectorMove::IsFinished() {
	SmartDashboard::PutNumber("error",
			fabs(SensorManager::getSensorManager()->getSensor(
			SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet() - target));
	return fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet() - target)
			< COLLECTOR_MOVE_TOLERANCE || MotorManager::getMotorManager()->getPID(PID_ID_COLLECTOR)->GetSetpoint() != target;

}

void CollectorMove::End() {
	SmartDashboard::PutBoolean("CollectorMoveRunning", false);
	MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
	char str[1024];
	sprintf(str, "CollectorMove END Called for target %f", target);
	writeToLogFile(LOGFILE_NAME, str);
}

void CollectorMove::Interrupted() {
	End(); //MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
}
