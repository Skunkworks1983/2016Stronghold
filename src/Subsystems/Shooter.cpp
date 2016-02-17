#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Shooter.h>

Shooter::Shooter():
		Subsystem("Shooter") {

	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
}

void Shooter::activateShooter(bool active) {
	//motorManager->enablePID();

}

float Shooter::getSpeed() {
	return 0.0;
}
