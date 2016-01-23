#include "SensorManager.h"
#include "../RobotMap.h"

SensorManager::SensorManager() :
		Subsystem("SensorManager")
{
	ahrs = new AHRS(SPI::Port::kMXP);
	lightSensor = new AnalogInput(LIGHT_SENSOR_PORT);
}

void SensorManager::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

float SensorManager::getYaw() {
	return ahrs->GetYaw();
}

float SensorManager::getPitch() {
	return ahrs->GetPitch();
}

float SensorManager::getRoll() {
	return ahrs->GetRoll();
}
float SensorManager::GetLightSensorVoltage(){

	return lightSensor->GetVoltage();


}

// Put methods for controlling this subsystem
// here. Call these from Commands.
