#include <Commands/MultiTool/ResetCollectorEncoder.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>

//TODO: Find the conversion ratio for encoder ticks to degrees
ResetShooterRotationEncoder::ResetShooterRotationEncoder() {
	sensorManager = SensorManager::getSensorManager();
}

void ResetShooterRotationEncoder::Initialize() {
	sensorManager->getSensor(SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->resetEncoder();
}

void ResetShooterRotationEncoder::Execute() {
}

bool ResetShooterRotationEncoder::IsFinished() {
	return true;
}

void ResetShooterRotationEncoder::End() {

}

void ResetShooterRotationEncoder::Interrupted() {

}
