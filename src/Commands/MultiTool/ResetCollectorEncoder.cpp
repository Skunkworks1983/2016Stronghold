#include <CANTalon.h>
#include <Commands/MultiTool/ResetCollectorEncoder.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>

//TODO: Find the conversion ratio for encoder ticks to degrees
ResetCollectorEncoder::ResetCollectorEncoder() {
	sensorManager = SensorManager::getSensorManager();
}

void ResetCollectorEncoder::Initialize() {
	sensorManager->getSensor(SENSOR_COLLECTOR_ROTATION_ENCODER_ID)->resetEncoder();
}

void ResetCollectorEncoder::Execute() {
}

bool ResetCollectorEncoder::IsFinished() {
	return true;
}

void ResetCollectorEncoder::End() {

}

void ResetCollectorEncoder::Interrupted() {

}
