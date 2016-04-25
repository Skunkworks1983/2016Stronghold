#include <Commands/Driving/DriveTowardsTower.h>
#include <DriverStation.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Services/Sensor.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

DriveTowardsTower::DriveTowardsTower(float speed, double P, double timeout) :
		speed(speed), P(P), timeout(timeout) {
	Requires(drivebase);
	sensorManager = SensorManager::getSensorManager();
	this->speed = speed;
	inputSpeed = speed;
}

DriveTowardsTower::~DriveTowardsTower() {
}

void DriveTowardsTower::Initialize() {
//	SensorManager::getSensorManager()->ZeroYaw();

	initialAngle = SensorManager::getSensorManager()->getYaw();

	if (timeout > 0) {
		SetTimeout(timeout);
	}
	speed = inputSpeed
			* (12.75 / DriverStation::GetInstance().GetBatteryVoltage());

	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);

	initialLeft = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	LOG_INFO("Start of drivetowardTower initialAngle %f", initialAngle);
}

void DriveTowardsTower::Execute() {
	const double cam_angle = CameraReader::getCameraReader()->getXAngle(0);

	if (oldCamAngle != cam_angle) {
		oldCamAngle = cam_angle;
	}

	double error = 0;

	if (fabs(cam_angle) >= 4100) {
		//we have the invalid value of 4200 (stupid check for floating point error
		error = 0;
		//update initial because we have lost camera so reset relative calculation
		initialAngle = SensorManager::getSensorManager()->getYaw();
	} else {
		//valid angle, calculate error
		error = SensorManager::getSensorManager()->getYaw() - initialAngle
				- cam_angle;
	}

	LOG_INFO("TowardsTower cam_angle: %f angle %f error %f error*P %f",
			cam_angle, SensorManager::getSensorManager()->getYaw(), error,
			error * P);

	const double leftSpeed = speed - error * P;
	const double rightSpeed = speed + error * P;

	drivebase->setLeftSpeed(leftSpeed >= 0 ? 0 : leftSpeed);
	drivebase->setRightSpeed(rightSpeed >= 0 ? 0 : rightSpeed);
}

bool DriveTowardsTower::IsFinished() {
	return IsTimedOut();
}

void DriveTowardsTower::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveTowardsTower::Interrupted() {
	End();
}
