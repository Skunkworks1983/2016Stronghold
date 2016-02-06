#include <AnalogInput.h>
#include <RobotMap.h>
#include <SPI.h>
#include <Subsystems/SensorManager.h>
#include "MotorManager.h"

SensorManager::SensorManager() :
		Subsystem("SensorManager")
{
	ahrsDead = false;
	try {
	    //ahrs = new AHRS(SPI::Port::kMXP);
	    ahrs = new AHRS(I2C::Port::kMXP);
	    ahrs->Reset();
	    counter = 0;
	    while(!ahrs->IsConnected()){
	    	printf("AHRS NOT CONNECTED\n");
	    	counter++;
	    	if(counter > AHRS_CYCLE_TIMEOUT) {
	    		std::cout << "AHRS DEAD, DEFAULTING TO ENCODER\n";
	    		ahrsDead = true;
	    		break;
	    	}
	    }
	    printf("Is the AHRS connected? %s", (ahrs->IsConnected() ? "Yes\n": "no\n"));
	} catch(std::exception * ex){
		std::string err_string = "Error instantiating navX MXP:  ";
		std::cout << err_string;
		err_string += ex->what();
		std::cout << err_string;
		std::cout << "AHRS DEAD, DEFAULTING TO ENCODER\n";
		ahrsDead = true;
	}
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
	return ahrs->GetAngle();
	//return ahrs->GetRoll();
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

// Put methods for controlling this subsystem
// here. Call these from Commands.
