#include <Commands/Driving/DriveStraightUntilLevel.h>
#include <DriverStation.h>
#include <RobotMap.h>
#include <Services/Sensor.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

DriveStraightUntilLevel::DriveStraightUntilLevel(float distance, float speed) {
	Requires(drivebase);
	sensorManager = SensorManager::getSensorManager();
	this->distance = ((distance / DRIVEBASE_FOOT_PER_TICK));
	this->speed = speed;
	initialYaw = 0.0;
	initialPosition = 0.0;
	initialLeft = 0.0;
	initialRight = 0.0;
	error = 0.0;
}

DriveStraightUntilLevel::~DriveStraightUntilLevel() {
}

void DriveStraightUntilLevel::Initialize() {
	initialYaw = sensorManager->getYaw();

	initialPitch = sensorManager->getPitch();

	speed *= 12.75 / DriverStation::GetInstance().GetBatteryVoltage();

	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);

	initialLeft = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	LOG_INFO("Using gyro for straight drive initial yaw %f", initialYaw);
}

void DriveStraightUntilLevel::Execute() {
	error = initialYaw - sensorManager->getYaw();

	if (error < -180.0) {
		error += 360.0;
	} else if (error > 180.0) {
		error -= 360.0;
	}

	double leftSpeed = ((1 / 15) * error + 1) * speed;
	double rightSpeed = (-1 * (1 / 15) * error + 1) * speed;
	LOG_INFO("Gyro: %f, Left: %f, Right: %f error %f", sensorManager->getYaw(),
			leftSpeed, rightSpeed, error);
	const double P = .07;
	drivebase->setLeftSpeed(speed + error * P);
	drivebase->setRightSpeed(speed - error * P);

	/*if (error <= 0) { //If its tilting to the left
	 drivebase->setLeftSpeed(speed);
	 drivebase->setRightSpeed(rightSpeed); //At 15 degree error to the left, no forward motion, just pivot
	 } else if (error >= 0) { //If its tilting to the right
	 drivebase->setLeftSpeed(leftSpeed); //Same but tilted to the right
	 drivebase->setRightSpeed(speed);
	 }*/
}

bool DriveStraightUntilLevel::IsFinished() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	bool leftPast = fabs(left - initialLeft) > fabs(distance);
	bool rightPast = fabs(right - initialRight) > fabs(distance);

	return (leftPast || rightPast) && fabs(sensorManager->getPitch() - initialPitch) < 1.0;
}

void DriveStraightUntilLevel::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveStraightUntilLevel::Interrupted() {
	End();
}
