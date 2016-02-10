#include <AnalogInput.h>
#include <RobotMap.h>
#include <SPI.h>
#include <Subsystems/MotorManager.h>
#include <Subsystems/SensorManager.h>


SensorManager::SensorManager() :
		Subsystem("SensorManager")
{
	ahrs = new AHRS(SPI::Port::kMXP);
	lightSensor = new AnalogInput(LIGHT_SENSOR_PORT);
}

SensorManager::~SensorManager()
{

}

void SensorManager::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
 SensorManager* SensorManager::getSensorManager(){
	 static SensorManager *instance;
	 if(instance == 0){
		 instance = new SensorManager();
	 }
	return instance;

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
float  SensorManager::GetAccelX(){

	return ahrs->GetWorldLinearAccelX();

}

float  SensorManager::GetAccelY(){
	return ahrs->GetWorldLinearAccelY();

}

float  SensorManager::GetAccelZ(){
	return ahrs->GetWorldLinearAccelZ();

}

double SensorManager::GetEncoderPosition(int ID) {
	return MotorManager::getMotorManager()->GetPosition(ID);

}
double SensorManager::GetSpeed(int ID){

	return MotorManager::getMotorManager()->GetSpeed(ID);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
