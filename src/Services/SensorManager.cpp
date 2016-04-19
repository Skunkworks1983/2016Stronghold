#include <Commands/Autonomous/AutoBase.h>
#include <I2C.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <exception>

#include "../../navx-mxp/cpp/include/AHRS.h"

SensorManager::SensorManager() {
	LOG_INFO("SensorManager Created #%u", count++);
#if USE_GYRO
	initGyro();
	sensors[SENSOR_GYRO_ID] = new Sensor(ahrs, 0, 360.0,
	SENSOR_GYRO_ID);
#endif
#if USE_CAMERA
	//sensors.insert(std::pair<int, Sensor*>(SENSOR_CAMERA_ID, new Sensor(CameraReader::getCameraReader())));
#endif
#if USE_DRIVEBASE
	sensors[SENSOR_DRIVE_BASE_LEFT_ENCODER_ID] = new Sensor(
	DRIVEBASE_LEFT_ENCODER_PORT, 0, 0, SENSOR_DRIVE_BASE_LEFT_ENCODER_ID);
	sensors[SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID] = new Sensor(
	DRIVEBASE_RIGHT_ENCODER_PORT, 0, 0, SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID,
	true);

	sensors[SENSOR_DRIVE_BASE_LEFT_SPEED_ID] = new SpeedSensor(
	DRIVEBASE_LEFT_ENCODER_PORT, 0, 0, SENSOR_DRIVE_BASE_LEFT_SPEED_ID);
	sensors[SENSOR_DRIVE_BASE_RIGHT_SPEED_ID] = new SpeedSensor(
	DRIVEBASE_RIGHT_ENCODER_PORT, 0, 0, SENSOR_DRIVE_BASE_RIGHT_SPEED_ID,
	true);
#endif
#if USE_SHOOTER
	sensors[SENSOR_SHOOTER_ENCODER_1_ID] = new Sensor(
	SHOOTER_MOTOR_LEFT_ENCODER_PORT, 0, 0, SENSOR_SHOOTER_ENCODER_1_ID, false);	//TODO: check if this is correct, encoder might be backward
	sensors[SENSOR_SHOOTER_ENCODER_2_ID] = new Sensor(
	SHOOTER_MOTOR_RIGHT_ENCODER_PORT, 0, 0, SENSOR_SHOOTER_ENCODER_2_ID, false);

	sensors[SENSOR_COLLECTOR_ROTATION_ENCODER_ID] = new Sensor(
	COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT,
	COLLECTOR_ROTATION_ENCODER_TOP_TICKS,
	COLLECTOR_ROTATION_ENCODER_COLLECT_TICKS,
	SENSOR_COLLECTOR_ROTATION_ENCODER_ID);

	sensors[SENSOR_COLLECTOR_ROLLER_ENCODER_ID] = new Sensor(
	COLLECTOR_ROLLER_ENCODER_PORT, 0, 0,
	SENSOR_COLLECTOR_ROLLER_ENCODER_ID);

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
	ahrs->DeleteSingletons();
	delete ahrs;
}

SensorManager* SensorManager::getSensorManager() {
	static SensorManager *instance = new SensorManager();
	return instance;
}

double SensorManager::wrapCheck(double value) {
	double ret = value;
	if (value >= 180.0) {
		ret -= 360.0;
	} else if (value <= -180.0) {
		ret += 360.0;
	}
	return ret;
}

void SensorManager::ZeroYaw() {
	if (ahrs != NULL) {
		LOG_INFO("AbsoluteHeading %f adding %f wrapCheck %f", absoluteHeading,
				ahrs->GetYaw(), wrapCheck(absoluteHeading + ahrs->GetYaw()))
		absoluteHeading = wrapCheck(absoluteHeading + ahrs->GetYaw());

		ahrs->ZeroYaw();
		ahrs->Reset();

		LOG_INFO("After zeroYaw %f", ahrs->GetYaw());
	}
}

void SensorManager::initGyro() {
	LOG_INFO("Initializing Gyro");
	if (ahrs == NULL) {
		try {
			ahrsDead = false;

			ahrs = new AHRS(I2C::Port::kMXP);
			counter = 0;
			while (!ahrs->IsConnected()) {
				counter++;
				if (counter > AHRS_CYCLE_TIMEOUT) {
					//LOG_ERROR("AHRS NOT CONNECTED");
					ahrsDead = true;
					break;
				}
			}
			counter = 0;
			while (ahrs->IsCalibrating()) {
				if (counter++ % 5 == 0) {
					//LOG_INFO("Counter %d", counter);
				}
				if (counter > 20000) {
					break;
				}
			}
			LOG_INFO("Is the AHRS connected? %s",
					(ahrs->IsConnected() ? "Yes\n" : "no\n"));
		} catch (std::exception * ex) {
			LOG_ERROR("Error instantiating navX MXP: %s \t", ex->what());

			ahrsDead = true;
		}
	}
}

float SensorManager::getYaw() {
	if (ahrs != NULL && ahrs->IsConnected() && !ahrs->IsCalibrating()) {
		double current = ahrs->GetYaw();
		//current += 180.0;

		return current;
	}
	return GYRO_NOT_CONNECTED_VALUE;
}

float SensorManager::getPitch() {
	if (ahrs != NULL && ahrs->IsConnected() && !ahrs->IsCalibrating()) {
		return ahrs->GetPitch();
	}
	return GYRO_NOT_CONNECTED_VALUE;
}

float SensorManager::getRoll() {
	if (ahrs != NULL && ahrs->IsConnected() && !ahrs->IsCalibrating()) {
		return ahrs->GetRoll();
	}
	return GYRO_NOT_CONNECTED_VALUE;
}

float SensorManager::getRawX() {
	return ahrs->GetRawGyroX();
}

float SensorManager::getRawY() {
	return ahrs->GetRawGyroY();
}

float SensorManager::getRawZ() {
	return ahrs->GetRawGyroZ();
}

float SensorManager::getAbsoluteGyroYaw(double target) {
	double ret = absoluteHeading;

	if (AutoBase::getObstacle() == Obstacle_cheval) {
		ret = wrapCheck(ret + 180.0);
	}

	LOG_INFO("Returning absolute gyro heading %f", ret);

	return ret;
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

AHRS* SensorManager::getGyro() {
	return ahrs;
}
