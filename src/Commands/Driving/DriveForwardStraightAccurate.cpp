#include <Commands/Driving/DriveForwardStraightAccurate.h>
#include <DriverStation.h>
#include <RobotMap.h>
#include <Services/Sensor.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

#define ENCODER_ERROR_BOUND_FEET 30
#define ENCODER_ERROR_TOLERANCE_FEET .25
#define DRIVE_FORWARD_MIN_OUTUPUT .15

#define USE_ERROR_FEET 3.0

#define FMIN_MAG(x,y) fabs(x) < fabs(y) ? x : y
#define FMAX_MAG(x,y) fabs(x) > fabs(y) ? x : y

DriveForwardStraightAccurate::DriveForwardStraightAccurate(float distance,
		float speed, double timeout) :
		timeout(timeout) {
	Requires(drivebase);
	sensorManager = SensorManager::getSensorManager();
	this->distance = ((distance / DRIVEBASE_FOOT_PER_TICK));
	this->speed = speed;
	this->inputSpeed = speed;
	initialYaw = 0.0;
	initialLeft = 0.0;
	initialRight = 0.0;
}

DriveForwardStraightAccurate::~DriveForwardStraightAccurate() {
}

void DriveForwardStraightAccurate::Initialize() {
//	SensorManager::getSensorManager()->ZeroYaw();

	speed = inputSpeed;

	if (timeout > 0) {
		SetTimeout(timeout);
	}
	initialYaw = sensorManager->getAngle();

	drivebase->setBrakeMode(true);

	speed *= 12.75 / DriverStation::GetInstance().GetBatteryVoltage();

	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);

	initialLeft = SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet();
	initialRight = SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet();

	LOG_INFO(
			"StraightDriveAccurate target %f initial yaw %f initialLeft %f initialRight %f ",
			distance * DRIVEBASE_FOOT_PER_TICK, initialYaw, initialLeft,
			initialRight);
}

void DriveForwardStraightAccurate::Execute() {
	double error = initialYaw - sensorManager->getAngle();

	if (error < -180.0) {
		error += 360.0;
	} else if (error > 180.0) {
		error -= 360.0;
	}

	const double left = ((initialLeft
			- SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet()))
			* DRIVEBASE_FOOT_PER_TICK;
	const double right = ((initialRight
			- SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet()))
			* DRIVEBASE_FOOT_PER_TICK;

	const double leftError = (distance * DRIVEBASE_FOOT_PER_TICK - (left));
	const double rightError = (distance * DRIVEBASE_FOOT_PER_TICK - (right));

	const double minError = FMIN_MAG(leftError, rightError);

	if (fabs(minError) < USE_ERROR_FEET) {
		drivebase->setLeftSpeed(
				FMAX_MAG(minError * .1,
						minError < 0 ? -DRIVE_FORWARD_MIN_OUTUPUT : DRIVE_FORWARD_MIN_OUTUPUT));
		drivebase->setRightSpeed(
				FMAX_MAG(minError * .1,
						minError < 0 ? -DRIVE_FORWARD_MIN_OUTUPUT : DRIVE_FORWARD_MIN_OUTUPUT));
	} else {
		const double P = .07;
		drivebase->setLeftSpeed(speed + error * P);
		drivebase->setRightSpeed(speed - error * P);
	}

	LOG_INFO("StraightDriveAccurate left %f right %f avgError %f distance %f", left,
			right, minError, distance * DRIVEBASE_FOOT_PER_TICK);
}

bool DriveForwardStraightAccurate::IsFinished() {
	const double left = ((initialLeft
			- SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet()))
			* DRIVEBASE_FOOT_PER_TICK;
	const double right = ((initialRight
			- SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet()))
			* DRIVEBASE_FOOT_PER_TICK;

	double leftError = (distance * DRIVEBASE_FOOT_PER_TICK - (left));
	double rightError = (distance * DRIVEBASE_FOOT_PER_TICK - (right));

	//if the error doesn't make sense assume the encoder is broken (20 feet is larger than anything we will see
	if (fabs(leftError) > ENCODER_ERROR_BOUND_FEET) {
		leftError = 0;
	}
	if (fabs(rightError) > ENCODER_ERROR_BOUND_FEET) {
		rightError = 0;
	}

	const double minError = FMIN_MAG(leftError, rightError);

	if (fabs(minError) < ENCODER_ERROR_TOLERANCE_FEET) {
		withinCount++;
	} else {
		withinCount = 0;
	}

	return withinCount > 10 || IsTimedOut();

}

void DriveForwardStraightAccurate::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveForwardStraightAccurate::Interrupted() {
	End();
}
