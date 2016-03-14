#include <CANTalon.h>
#include <I2C.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/Motor.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <cstdio>
#include <exception>
#include <iostream>
#include <string>

#include "../../navx-mxp/cpp/include/AHRS.h"

Sensor::Sensor(unsigned CANTalonEncoderPort, float lowRange, float highRange,
		unsigned ID, bool reversed) :
		ID(ID), lowRange(lowRange), highRange(highRange), reversed(reversed) {
	Motor * motor = MotorManager::getMotorManager()->getMotor(
			CANTalonEncoderPort);
	if (motor != NULL) {
		char str[1024];
		sprintf(str, "Created Sensor with talon on ID %d", CANTalonEncoderPort);
		Logger::getLogger()->log(str, Info);
		this->talon = motor->talon;
		talon->SetEncPosition(0);
		talon->SetPosition(0);
		talon->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		talon->GetAnalogIn();
		talon->GetPulseWidthPosition();
	} else {
		char str[1024];
		sprintf(str, "MotorIs null!!! port: %d", CANTalonEncoderPort);
		Logger::getLogger()->log(str, Info);
	}
	this->src = NULL;
	this->ahrs = NULL;
}

Sensor::Sensor(PIDSource *src, float lowRange, float highRange, unsigned ID,
bool reversed) :
		ID(ID), lowRange(lowRange), highRange(highRange), reversed(reversed) {
	this->talon = NULL;
	this->src = src;
	this->ahrs = NULL;
}

Sensor::Sensor(AHRS * ahrs, float lowRange, float highRange, unsigned ID,
bool reversed) :
		ahrs(ahrs), lowRange(lowRange), highRange(highRange), ID(ID), reversed(
				reversed), src(NULL), talon(NULL) {
	if (ahrs != NULL) {
		ahrs->SetPIDSourceType(PIDSourceType::kDisplacement);
		ahrs->ZeroYaw();
		ahrs->Reset();
		ahrs->ResetDisplacement();
	}
}

void Sensor::resetEncoder() {
	if (this->talon != NULL) {
		this->talon->SetEncPosition(0);
	}
}

Sensor::Sensor(CANTalon *canTalon, float lowRange, float highRange, unsigned ID,
bool reversed) :
		talon(canTalon), src(NULL), ID(ID), lowRange(lowRange), highRange(
				highRange), reversed(reversed) {
	talon->SetEncPosition(0);
	talon->SetPosition(0);
	talon->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
}

double Sensor::PIDGet() {
	if (talon != NULL) {
		if (reversed) {
			return (double) -talon->GetEncPosition();
		} else {
			return (double) talon->GetEncPosition();
		}
	} else if (ahrs != NULL) {
//		char str[1024];
//		sprintf(str, "PIDSource returning ahrs GetYaw(), Gryo: %f",
//				ahrs->GetYaw());
//		Logger::getLogger()->log(str, Info);
		return ahrs->GetYaw() - SensorManager::getSensorManager()->initialYaw;
	} else if (src != NULL) {
		char str[1024];
		sprintf(str, "PIDSource is returning PIDGet");
		Logger::getLogger()->log(str, Info);
		return src->PIDGet();
	} else {
		char str[1024];
		sprintf(str,
				"%s:%d Sensor is returning a 0.0 because talon && src are NULL",
				__PRETTY_FUNCTION__, __LINE__);
		Logger::getLogger()->log(str, Info);
		return 0.0;
	}
}

//ticks per 100 ms
double Sensor::getSpeed() {
	//from CANTalon.cpp  * The speed units will be in the sensor's native ticks per 100ms.*
	if (talon != NULL) {
		return talon->GetSpeed() * (reversed ? -1 : 1);
	}
	return 0.0;
}

int Sensor::getAbsolutePosition() {
	return talon->GetPulseWidthPosition() * (reversed ? -1 : 1);
}

SensorManager::SensorManager() {
	char str[1024];
	sprintf(str, "SensorManager Created #%u", count++);
	Logger::getLogger()->log(str, Info);
#if USE_GYRO
	//Sensor(AHRS * ahrs, float lowRange, float highRange, unsigned ID, bool reversed = false);

	initGyro();
	sensors[SENSOR_GYRO_ID] = new Sensor(ahrs, -180, //REMOVE MAGIC NUMBER
			180, //DITTO
			SENSOR_GYRO_ID);
	//sensors.insert(std::pair<int, Sensor*>(SENSOR_GYRO_ID, new Sensor(ahrs)));
	//todo: FIX THIS
#endif
#if USE_CAMERA
	sensors.insert(std::pair<int, Sensor*>(SENSOR_CAMERA_ID, new Sensor(CameraReader::getCameraReader())));
#endif
#if USE_DRIVEBASE
	sensors[SENSOR_DRIVE_BASE_LEFT_ENCODER_ID] = new Sensor(
	DRIVEBASE_LEFT_ENCODER_PORT, 0, 0, SENSOR_DRIVE_BASE_LEFT_ENCODER_ID);
	sensors[SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID] = new Sensor(
	DRIVEBASE_RIGHT_ENCODER_PORT, 0, 0, SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID,
	true);
#endif
#if USE_SHOOTER
	sensors[SENSOR_SHOOTER_ENCODER_1_ID] = new Sensor(
	SHOOTER_1_ENCODER_PORT, 0, 0, SENSOR_SHOOTER_ENCODER_1_ID, true);
	sensors[SENSOR_SHOOTER_ENCODER_2_ID] = new Sensor(
	SHOOTER_2_ENCODER_PORT, 0, 0, SENSOR_SHOOTER_ENCODER_2_ID, false);

	sensors[SENSOR_COLLECTOR_ROTATION_ENCODER_ID] = new Sensor(
	COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT,
	COLLECTOR_ROTATION_ENCODER_TOP_TICKS,
	COLLECTOR_ROTATION_ENCODER_COLLECT_TICKS,
	SENSOR_COLLECTOR_ROTATION_ENCODER_ID);

	sensors[SENSOR_COLLECTOR_ROLLER_ENCODER_ID] = new Sensor(
	COLLECTOR_ROLLER_ENCODER_PORT, 0, 0,
	SENSOR_COLLECTOR_ROLLER_ENCODER_ID);
	/*sensors.insert(
	 std::pair<unsigned, Sensor*>(SENSOR_COLLECTOR_ROLLER_ENCODER_ID,
	 new Sensor(COLLECTOR_ROLLER_ENCODER_PORT,
	 SENSOR_COLLECTOR_ROLLER_ENCODER_ID)));*/
#endif
#if USE_CLIMBER
	sensors[SENSOR_CLIMBER_WINCH_ENCODER] = new Sensor(
	CLIMBER_WINCH_ENCODER_PORT,
	CLIMBER_WINCH_DOWN_POSITION,
	CLIMBER_WINCH_UP_POSITION,
	SENSOR_CLIMBER_WINCH_ENCODER);

	sensors[SENSOR_CLIMBER_ARM_ENCODER] = new Sensor(
	CLIMBER_ARM_ENCODER_PORT,
	CLIMBER_ARM_DOWN_POSITION,
	CLIMBER_ARM_UP_POSITION,
	SENSOR_CLIMBER_ARM_ENCODER, true);
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
	static SensorManager *instance = new SensorManager();
	return instance;
}

void SensorManager::initGyro() {
	Logger::getLogger()->log("Initializing Gyro", Debug);
	std::cout << "Reached initGyro" << std::endl;
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
		printf("Is the AHRS connected? %s",
				(ahrs->IsConnected() ? "Yes\n" : "no\n"));
	} catch (std::exception * ex) {
		std::string err_string = "Error instantiating navX MXP:  ";
		std::cout << err_string;
		err_string += ex->what();
		std::cout << err_string;
		std::cout << "AHRS DEAD, DEFAULTING TO ENCODER\n";
		ahrsDead = true;
	}
	if (!ahrsDead) {
		initialYaw = ahrs->GetYaw();
	}
}

float SensorManager::getYaw() {
	if (ahrs != NULL) {
		return ahrs->GetYaw();
	}
	return 0.0;
}

float SensorManager::getPitch() {
	if (ahrs != NULL) {
		return ahrs->GetPitch();
	}
	return 0.0;
}

float SensorManager::getRoll() {
	if (ahrs != NULL) {
		return ahrs->GetAngle();
	}
	return 0.0;
}

float SensorManager::GetAccelX() {
	if (ahrs != NULL) {
		return ahrs->GetWorldLinearAccelX();
	}
	return 0.0;

}

float SensorManager::GetAccelY() {
	if (ahrs != NULL) {
		return ahrs->GetWorldLinearAccelY();
	}
	return 0.0;

}

float SensorManager::GetAccelZ() {
	if (ahrs != NULL) {
		return ahrs->GetWorldLinearAccelZ();
	}
	return 0.0;

}

float Sensor::getLowRange() {
	return lowRange;
}
float Sensor::getHighRange() {
	return highRange;
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

AHRS* SensorManager::getGyro(){
	return ahrs;
}
