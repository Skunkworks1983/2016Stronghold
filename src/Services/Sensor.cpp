/*
 * Sensor.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: S-4020395
 */

#include <PIDSource.h>
#include <Services/Motor.h>
#include <Services/MotorManager.h>
#include <Services/Sensor.h>
#include <Services/SensorManager.h>
#include <RobotMap.h>

double SpeedSensor::PIDGet() {
	if (talon != NULL) {
		if (reversed) {
			return (double) -talon->GetSpeed();
		} else {
			return (double) talon->GetSpeed();
		}
	}
	return 0.0;
}

SpeedSensor::SpeedSensor(unsigned CANTalonEncoderPort, float lowRange,
		float highRange, unsigned ID, bool reversed) :
		Sensor(CANTalonEncoderPort, lowRange, highRange, ID, reversed) {
}

Sensor::Sensor(unsigned CANTalonEncoderPort, float lowRange, float highRange,
		unsigned ID, bool reversed) :
		ID(ID), lowRange(lowRange), highRange(highRange), reversed(reversed) {
	Motor * motor = MotorManager::getMotorManager()->getMotor(
			CANTalonEncoderPort);
	if (motor != NULL) {
		LOG_INFO("Created Sensor with talon on ID %d", CANTalonEncoderPort);
		this->talon = motor->talon;
		//talon->SetEncPosition(0);
		talon->SetPosition(0);
		if (talon->IsSensorPresent(CANTalon::FeedbackDevice::AnalogEncoder)) {
			LOG_INFO("Talon port %u has AnalogEncoder", CANTalonEncoderPort);
		} else if (talon->IsSensorPresent(
				CANTalon::FeedbackDevice::CtreMagEncoder_Absolute)) {
			LOG_INFO("Talon port %u has CtreMagEncoder_Absolute",
					CANTalonEncoderPort);
		} else if (talon->IsSensorPresent(
				CANTalon::FeedbackDevice::CtreMagEncoder_Relative)) {
			LOG_INFO("Talon port %u has CtreMagEncoder_Relative",
					CANTalonEncoderPort);
		} else if (talon->IsSensorPresent(
				CANTalon::FeedbackDevice::QuadEncoder)) {
			LOG_INFO("Talon port %u has QuadEncoder", CANTalonEncoderPort);
		} else if (talon->IsSensorPresent(
				CANTalon::FeedbackDevice::PulseWidth)) {
			LOG_INFO("Talon port %u has PulseWidth", CANTalonEncoderPort);
		} else if (talon->IsSensorPresent(
				CANTalon::FeedbackDevice::EncFalling)) {
			LOG_INFO("Talon port %u has EncFalling", CANTalonEncoderPort);
		} else if (talon->IsSensorPresent(
				CANTalon::FeedbackDevice::EncRising)) {
			LOG_INFO("Talon port %u has EncRising", CANTalonEncoderPort);
		}
	} else {
		LOG_INFO("MotorIs null!!! port: %d", CANTalonEncoderPort);
	}
}

Sensor::Sensor(PIDSource *src, float lowRange, float highRange, unsigned ID,
bool reversed) :
		src(src), ID(ID), lowRange(lowRange), highRange(highRange), reversed(
				reversed) {
}

Sensor::Sensor(AHRS * ahrs, float lowRange, float highRange, unsigned ID,
bool reversed) :
		ahrs(ahrs), lowRange(lowRange), highRange(highRange), ID(ID), reversed(
				reversed) {
	if (ahrs != NULL) {
		ahrs->SetPIDSourceType(PIDSourceType::kDisplacement);
		ahrs->ZeroYaw();
		ahrs->Reset();
		ahrs->ResetDisplacement();
		LOG_INFO("NAVX has been reset?");
	} else {
		LOG_ERROR("NAVX IS NULL SO I CANNOT RESET THE GYRO STUPID");
	}
}

Sensor::Sensor(CANTalon *canTalon, float lowRange, float highRange, unsigned ID,
bool reversed) :
		talon(canTalon), src(NULL), ID(ID), lowRange(lowRange), highRange(
				highRange), reversed(reversed) {
	talon->SetEncPosition(0);
	talon->SetPosition(0);
	talon->SetControlMode(CANTalon::kPercentVbus);
}

Sensor::~Sensor() {
	delete ahrs;
	delete talon;
}

void Sensor::resetEncoder() {
	if (this->talon != NULL) {
		this->talon->SetEncPosition(0);
	}
}

double Sensor::PIDGet() {
	if (talon != NULL) {
		if (reversed) {
			return (double) -talon->GetPosition();
		} else {
			return (double) talon->GetPosition();
		}
	} else if (ahrs != NULL) {
		return SensorManager::getSensorManager()->getYaw();
	} else if (src != NULL) {
		LOG_INFO("PIDSource is returning PIDGet");
		return src->PIDGet();
	} else {
		LOG_INFO("Sensor is returning a 0.0 because talon && src are NULL");
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
