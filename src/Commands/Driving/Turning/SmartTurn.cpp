#include <Commands/Driving/Turning/SmartTurn.h>
#include <Services/MotorManager.h>
#include <Services/Sensor.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

SmartTurn::SmartTurn(double targetDegrees, bool absolute) :
		target(targetDegrees), absolute(absolute) {
	Requires(drivebase);
	sensorManager = SensorManager::getSensorManager();
}

// Called just before this Command runs the first time
void SmartTurn::Initialize() {
	current_level = GYRO;
	//if gyro is not connected at start of turn, fall back to encoder
	if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() == GYRO_NOT_CONNECTED_VALUE) {
		current_level = ENCODER;
	}

	MotorManager::getMotorManager()->setPID(PID_ID_DRIVEBASE_ROT, P, I, D);

	onCount = 0;

	//record inital encoder even if not in encoder mode in case gyro breaks in middle of command
	initialLeft = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	if (absolute) {
		target += 0.0;
	} else {
		if (current_level == GYRO) {
			if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() + target
					> 180.0) {
				target += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
				target -= 180.0;
				target *= -1;
			} else if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet()
					+ target < -180.0) {
				target += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
				target += 180.0;
				target *= -1;
			} else {
				target += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
			}

		} else if (current_level == ENCODER) {
			target = 3000 * (target / 360.0);
		}
	}

	const double error = target
			- sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	if (error > 0) {
		drivebase->setLeftSpeed(initialSpeed);
		drivebase->setRightSpeed(-initialSpeed);
	} else {
		drivebase->setLeftSpeed(-initialSpeed);
		drivebase->setRightSpeed(initialSpeed);
	}
}

// Called repeatedly when this Command is scheduled to run
void SmartTurn::Execute() {
	if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() == GYRO_NOT_CONNECTED_VALUE) {
		current_level = ENCODER;
	} else {
		current_level = GYRO;
	}

	if (count++ > 25 && !alreadyRan) {
		//drivebase->setLeftSpeed(0);
		//drivebase->setRightSpeed(0);
		MotorManager::getMotorManager()->enablePID(PID_ID_DRIVEBASE_ROT,
				target);
		alreadyRan = true;
	}

}

// Make this return true when this Command no longer needs to run execute()
bool SmartTurn::IsFinished() {
	if (current_level == GYRO) {
		const double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

		if (fabs(yaw - target) < DEGREE_TOLERANCE) {
			onCount++;
		} else {
			onCount = 0;
		}
		return onCount > 20;
	}
	if (current_level == ENCODER) {
		double leftEncoder = fabs(sensorManager->getSensor(
		SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
		double rightEncoder = fabs(sensorManager->getSensor(
		SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

		const bool leftPast = fabs(leftEncoder - initialLeft) > target;
		const bool rightPast = fabs(rightEncoder - initialRight) > target;

		return leftPast || rightPast;
	}
	return false;
}

// Called once after isFinished returns true
void SmartTurn::End() {
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SmartTurn::Interrupted() {
	End();
}
