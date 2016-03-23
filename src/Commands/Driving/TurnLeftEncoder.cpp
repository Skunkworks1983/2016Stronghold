#include <Commands/Driving/TurnLeftEncoder.h>
#include <RobotMap.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <Services/Logger.h>
#include <cmath>

TurnLeftEncoder::TurnLeftEncoder(double degrees, double speed) :
		degrees(degrees), speed(speed) {
	Requires(drivebase);
	initialEncoderTick = 0.0;
	sensorManager = SensorManager::getSensorManager();
}

TurnLeftEncoder::~TurnLeftEncoder() {
}

void TurnLeftEncoder::Initialize() {
	initialEncoderTick = sensorManager->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet();

	drivebase->setLeftSpeed(-speed);
	drivebase->setRightSpeed(speed);
}

void TurnLeftEncoder::Execute() {

}

bool TurnLeftEncoder::IsFinished() {
	const double targetTicks = 3000 * (degrees / 360.0);

	double leftEncoder = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double rightEncoder = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	//check if average of encoder ticks is larger than target
	return fabs((leftEncoder + rightEncoder) / 2 - initialEncoderTick)
			> targetTicks;
}

void TurnLeftEncoder::End() {
	LOG_INFO("TurnDegreeEncoder ENDED!");
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
}

void TurnLeftEncoder::Interrupted() {
	End();
}
