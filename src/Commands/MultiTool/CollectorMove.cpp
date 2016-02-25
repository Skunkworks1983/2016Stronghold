#include <Commands/MultiTool/CollectorMove.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>
#include <cstdio>

//TODO: Find the conversion ratio for encoder ticks to degrees
CollectorMove::CollectorMove(CollectorPosition pos) {
	switch (pos) {
	case TOP:
		target = COLLECTOR_ROTATION_ENCODER_TOP_TICKS;
		break;
	case FLOOR:
		target = COLLECTOR_ROTATION_ENCODER_FLOOR_TICKS;
		break;
	case MID:
		target = COLLECTOR_ROTATION_ENCODER_MID_TICKS;
		break;
	}

	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
}

void CollectorMove::Initialize() {
	motorManager->enablePID(PID_ID_COLLECTOR, target);
}

void CollectorMove::Execute() {
	double enc =
			sensorManager->getSensor(SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet();
	char str[1024];
	sprintf(str, "EncoderPosition: %f, Target: %f", enc, target);
	writeToLogFile(LOGFILE_NAME, str);
}

bool CollectorMove::IsFinished() {
	if (fabs(sensorManager->getSensor(SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->PIDGet() - target)
			< 50) {
		return true;
	}
	return false;

}

void CollectorMove::End() {
	//collector->setRotatorSpeed(0.0);
	//MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
}

void CollectorMove::Interrupted() {
	End();
}
