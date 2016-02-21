#include <CANTalon.h>
#include <I2C.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <cstdio>
#include <exception>
#include <iostream>
#include <string>

#include "../../navx-mxp/cpp/include/AHRS.h"

Sensor::Sensor(unsigned CANTalonEncoderPort) {
	Motor * motor = MotorManager::getMotorManager()->getMotor(
			CANTalonEncoderPort);
	if (motor != NULL) {
		char str[1024];
		sprintf(str, "Created Sensor with talon on ID %d", CANTalonEncoderPort);
		writeToLogFile(LOGFILE_NAME, str);
		this->talon = motor->talon;
	} else {
		char str[1024];
		sprintf(str, "MotorIs null!!! port: %d", CANTalonEncoderPort);
		writeToLogFile(LOGFILE_NAME, str);
	}
	this->src = NULL;
}

Sensor::Sensor(PIDSource *src) {
	this->talon = NULL;
	this->src = src;
}

Sensor::Sensor(CANTalon *canTalon) {
	this->talon = canTalon;
	this->src = NULL;
}

double Sensor::PIDGet() {
	if (talon != NULL) {
		char str[1024];
		sprintf(str, "Talon is returning PIDGet");
		writeToLogFile(LOGFILE_NAME, str);
		return talon->PIDGet();
	} else if (src != NULL) {
		char str[1024];
		sprintf(str, "PIDSource is returning PIDGet");
		writeToLogFile(LOGFILE_NAME, str);
		return src->PIDGet();
	} else {
		char str[1024];
		sprintf(str, "Sensor is returning a 0.0 because talon && src are NULL");
		writeToLogFile(LOGFILE_NAME, str);
		return 0.0;
	}
}

SensorManager::SensorManager() {
	sensors = std::map<unsigned, Sensor*>();
	char str[1024];
	sprintf(str, "SensorManager Created");
	writeToLogFile(LOGFILE_NAME, str);
#if USE_GYRO
	initGyro();
	sensors.insert(std::pair<int, Sensor*>(SENSOR_GYRO_ID, new Sensor(ahrs)));
#endif
#if USE_CAMERA
	sensors.insert(std::pair<int, Sensor*>(SENSOR_CAMERA_ID, new Sensor(CameraReader::getCameraReader())));
#endif
#if USE_DRIVEBASE
	sensors[SENSOR_DRIVE_BASE_LEFT_ENCODER_ID] = new Sensor(
	DRIVEBASE_LEFTMOTOR_2_PORT);
	sensors[SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID] = new Sensor(
	DRIVEBASE_RIGHTMOTOR_2_PORT);
#endif
#if USE_COLLECTOR
	sensors.insert(std::pair<int, Sensor*>(SENSOR_COLLECTOR_ROTATION_ENCODER_ID, new Sensor(SENSOR_COLLECTOR_ROTATION_ENCODER_ID)));
	sensors.insert(std::pair<int, Sensor*>(SENSOR_COLLECTOR_ROLLER_ENCODER_ID, new Sensor(SENSOR_COLLECTOR_ROLLER_ENCODER_ID)));
#endif
#if USE_SHOOTER
	sensors.insert(std::pair<int, Sensor*>(SENSOR_SHOOTER_ENCODER_1_ID, new Sensor(SENSOR_SHOOTER_ENCODER_1_ID)));
	sensors.insert(std::pair<int, Sensor*>(SENSOR_SHOOTER_ENCODER_2_ID, new Sensor(SENSOR_SHOOTER_ENCODER_2_ID)));
#endif
#if USE_CLIMBER
	sensors.insert(std::pair<int, Sensor*>(SENSOR_CLIMBER_WINCH_ENCODER, new Sensor(SENSOR_CLIMBER_WINCH_ENCODER)));
	sensors.insert(std::pair<int, Sensor*>(SENSOR_CLIMBER_ARM_ENCODER, new Sensor(SENSOR_CLIMBER_ARM_ENCODER)));
#endif
}

SensorManager::~SensorManager() {
	std::map<unsigned, Sensor*>::iterator it = sensors.begin();
	for (; it != sensors.end(); ++it) {
		delete (*it).second;
	}
	sensors.clear();
	delete ahrs;
}

SensorManager* SensorManager::getSensorManager() {
	static SensorManager *instance = NULL;
	if (instance == NULL) {
		instance = new SensorManager();
	}
	return instance;
}

void SensorManager::initGyro() {
	try {
		ahrsDead = false;
		//ahrs = new AHRS(SPI::Port::kMXP); Any of the three work. Probably.
		ahrs = new AHRS(I2C::Port::kMXP);
		ahrs->Reset();
		counter = 0;
		while (!ahrs->IsConnected()) {
			//printf("AHRS NOT CONNECTED\n");
			counter++;
			if (counter > AHRS_CYCLE_TIMEOUT) {
				std::cout << "AHRS DEAD, DEFAULTING TO ENCODER\n";
				ahrsDead = true;
				break;
			}
		}
		//printf("Is the AHRS connected? %s", (ahrs->IsConnected() ? "Yes\n" : "no\n"));
	} catch (std::exception * ex) {
		std::string err_string = "Error instantiating navX MXP:  ";
		std::cout << err_string;
		err_string += ex->what();
		std::cout << err_string;
		std::cout << "AHRS DEAD, DEFAULTING TO ENCODER\n";
		ahrsDead = true;
	}
	if(!ahrsDead) {
		initialYaw = ahrs->GetYaw();
	}
}

float SensorManager::getYaw() {
	return ahrs->GetYaw();
}

float SensorManager::getPitch() {
	return ahrs->GetPitch();
}

float SensorManager::getRoll() {
	return ahrs->GetAngle();
}

float SensorManager::GetAccelX() {

	return ahrs->GetWorldLinearAccelX();

}

float SensorManager::GetAccelY() {
	return ahrs->GetWorldLinearAccelY();

}

float SensorManager::GetAccelZ() {
	return ahrs->GetWorldLinearAccelZ();

}

double SensorManager::GetEncoderPosition(int ID) {
	return MotorManager::getMotorManager()->GetPosition(ID);

}
double SensorManager::GetSpeed(int ID) {
	return MotorManager::getMotorManager()->GetSpeed(ID);
}

Sensor* SensorManager::getSensor(unsigned ID) {
	if (sensors.count(ID) != 0) {
		return sensors[ID];
	} else {
		return NULL;
	}
}
