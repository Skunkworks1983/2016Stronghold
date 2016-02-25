#include <Commands/Driving/TurnRightEncoder.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>
#include <cstdio>

TurnRightEncoder::TurnRightEncoder(double degrees) :
		degrees(degrees) {
	Requires(drivebase);
	initialLeft = 0;
	initialRight = 0;
}

TurnRightEncoder::~TurnRightEncoder() {
}

void TurnRightEncoder::Initialize() {
	initialLeft = SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet();
	initialRight = SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet();
	double speed = .5;
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(-speed);
}

void TurnRightEncoder::Execute() {

}

bool TurnRightEncoder::IsFinished() {
	double end = 3000;
	return fabs(
			(fabs(SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet() - initialLeft)
					+ fabs(SensorManager::getSensorManager()->getSensor(
					SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet() - initialRight))
					/ 2) > end * (degrees / 360.0);
}

void TurnRightEncoder::End() {
	char str[1024];
	sprintf(str, "TurnDegreeEncoder ENDED!");
	writeToLogFile(LOGFILE_NAME, str);
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
}

void TurnRightEncoder::Interrupted() {
	End();
}
